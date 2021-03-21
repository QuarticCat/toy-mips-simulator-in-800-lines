#pragma once

#include <cctype>
#include <charconv>
#include <exception>
#include <functional>
#include <istream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>

#include "instr.hpp"

struct ParseError: std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Assembler {
    std::tuple<Memory, u32> parse_asm(std::istream& is) {
        while (std::getline(is, this->line)) {
            this->line_begin = this->line.begin();
            Token token = this->parse_token();

            while (*token.end() == ':') {  // label (maybe multiple)
                this->handle_label(token);
                token = this->parse_token();
            }

            if (token.empty()) continue;  // line consumed

            if (*token.begin() == '.')  // assembler directive
                this->handle_direc(token);
            else if (instr_map.contains(token))  // instruction
                this->handle_instr(token);
            else
                throw ParseError("Unknown token!");
        }
        u32 text_end = text_low + ((this->text_ptr - (u32*)&this->mem[0]) << 2u);
        return {std::move(this->mem), text_end};
    }

  private:
    struct Wait {
        u32* instr_ptr;
        uint8_t addr_offset;
        Type type;
    };

    // GCC and Clang haven't support "heterogeneous lookup for unordered containers" yet.
    std::map<std::string, u32*, std::less<>> label_map{};
    std::multimap<std::string, Wait, std::less<>> wait_map{};
    Memory mem{};
    u32* text_ptr = (u32*)&mem[0];
    u32* data_ptr = (u32*)&mem[data_low - text_low];
    std::string line{};
    std::string::iterator line_begin{};

    /// Return first token in given range.
    Token parse_token() {
        constexpr auto token_char = [](char c) {
            return c == '-' || std::isalnum(c) || c == '$' || c == '.' || c == '_';
        };
        auto l = this->line_begin, end = this->line.end();
        while (l != end && *l != '#' && !token_char(*l)) ++l;
        if (*l == '#') return {end, this->line_begin = end};
        auto r = l;
        while (r != end && token_char(*r)) ++r;
        return {l, this->line_begin = r};
    }

    /// Parse register names, e.g. "$zero" -> 0.
    static u32 token_to_reg(Token token) {
        // clang-format off
        static std::unordered_map<Token, u32> reg_map = {
            {"$zero",  0}, {"$at",    1}, {"$v0",    2}, {"$v1",    3},
            {"$a0",    4}, {"$a1",    5}, {"$a2",    6}, {"$a3",    7},
            {"$t0",    8}, {"$t1",    9}, {"$t2",   10}, {"$t3",   11},
            {"$t4",   12}, {"$t5",   13}, {"$t6",   14}, {"$t7",   15},
            {"$s0",   16}, {"$s1",   17}, {"$s2",   18}, {"$s3",   19},
            {"$s4",   20}, {"$s5",   21}, {"$s6",   22}, {"$s7",   23},
            {"$t8",   24}, {"$t9",   25}, {"$k0",   26}, {"$k1",   27},
            {"$gp",   28}, {"$sp",   29}, {"$fp",   30}, {"$ra",   31},
        };
        // clang-format on
        if (reg_map.contains(token)) return reg_map.at(token);
        throw ParseError("Unknown register!");
    }

    /// Parse numbers.
    template<class T>
    static T token_to_num(Token token) {
        T ret = 0;
        std::from_chars(&*token.begin(), &*token.end(), ret);
        return ret;
    }

    /// Calculate address number.
    u32 calc_addr(u32* target_ptr, u32* instr_ptr, Type type) {
        return type == Type::I ? (u16)(target_ptr - instr_ptr - 1)
                               : (text_low >> 2u) + (target_ptr - (u32*)&this->mem[0]);
    }

    void handle_label(Token token) {
        this->label_map.insert({std::string(token), this->text_ptr});
        auto [begin, end] = this->wait_map.equal_range(token);
        for (auto iter = begin; iter != end; ++iter) {
            auto [instr_ptr, addr_offset, type] = iter->second;
            *instr_ptr |= calc_addr(this->text_ptr, instr_ptr, type) << addr_offset;
        }
        this->wait_map.erase(begin, end);
    }

    void handle_direc(Token token) {
        // Small amount of comparisons between short strings can be optimized to be super fast.
        if (token == ".text" || token == ".data") return;
        if (token == ".ascii") return this->read_str_literal<false>();
        if (token == ".asciiz") return this->read_str_literal<true>();
        if (token == ".word") return this->read_numbers<u32>();
        if (token == ".half") return this->read_numbers<u16>();
        if (token == ".byte") return this->read_numbers<u8>();
        throw ParseError("Unknown directive!");
    }

    template<bool NullTerminate>
    void read_str_literal() {
        auto &l = this->line_begin, r = this->line.end();
        auto ptr = (char*)this->data_ptr;
        while (*l != '"') ++l;
        for (++l; l != r && *l != '"'; ++l) {
            if (*l == '\\') {
                // clang-format off
                switch (*++l) {
                case 'n': *ptr++ = '\n'; break;
                case 't': *ptr++ = '\t'; break;
                case '"': *ptr++ = '\"'; break;
                case '0': *ptr++ = '\0'; break;
                case '\\': *ptr++ = '\\'; break;
                default: throw ParseError("Unknown escape character!");
                }
                // clang-format on
            } else {
                *ptr++ = *l;
            }
        }
        if constexpr (NullTerminate) *ptr++ = '\0';
        this->data_ptr = (u32*)(((size_t)ptr + 3) & ~0b11);
    }

    template<class T>
    void read_numbers() {
        auto ptr = (T*)this->data_ptr;
        for (Token token; !(token = this->parse_token()).empty();) *ptr++ = token_to_num<T>(token);
        this->data_ptr = (u32*)(((size_t)ptr + 3) & ~0b11);
    }

    void handle_instr(Token token) {
        auto instr = instr_map.at(token);
        std::array<u32, 3> args{};
        for (size_t i: {0, 1, 2}) {
            token = this->parse_token();
            if (token.empty()) break;
            char first = *token.begin();
            if (first == '$') {  // register
                args[i] = token_to_reg(token);
            } else if (first == '-' || std::isdigit(first)) {  // immediate
                args[i] = instr.type == Type::I ? token_to_num<i32>(token) & 0xffff
                                                : token_to_num<u32>(token) & 0x3ffffff;
            } else if (auto iter = this->label_map.find(token);
                       iter != this->label_map.end()) {  // label
                args[i] = calc_addr(iter->second, this->text_ptr, instr.type);
            } else {  // wait label
                Wait wait{this->text_ptr, instr.offsets[i], instr.type};
                wait_map.insert({std::string(token), wait});
            }
        }
        *this->text_ptr++ = instr.gen(args);
    }
};

inline auto assemble(std::istream& in) {
    return Assembler{}.parse_asm(in);
}
