#pragma once

#include <fcntl.h>
#include <unistd.h>

#include <array>
#include <bit>
#include <cstdio>
#include <exception>
#include <istream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>

#include "def.hpp"

// Already disabled strict-aliasing, I am free as a bird! (to do type punning)

// C++-style type casting is disgusting, go away!

struct TrapError: std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct ExitError: std::runtime_error {
    ExitError(const std::string& msg, u32 code): std::runtime_error(msg), _code(code) {}

    [[nodiscard]] u32 code() const noexcept {
        return this->_code;
    }

  private:
    u32 _code;
};

#define TRAP(msg)  (throw TrapError("Trap: " msg))
#define EXIT(code) (throw ExitError("Exit!", code))

struct Simulator {
    std::istream& in;
    std::ostream& out;
    Memory mem;
    std::array<u32, 32> regs{};
    u32 hi{};
    u32 lo{};
    u32 pc = text_low;
    u32 text_end;
    u32 heap_top = heap_low;

    Simulator(std::istream& in, std::ostream& out, Memory mem, u32 text_end)
        : in(in), out(out), mem(std::move(mem)), text_end(text_end) {
        this->regs[28] = data_low;
        this->regs[29] = stack_high;
    }

    template<class T>
    T& at(u32 addr) noexcept {
        return (T&)this->mem[addr - text_low];
    }

    void syscall() {
        switch (this->regs[2]) {
        case 1:  // print_int
            this->out << (i32)this->regs[4];
            break;
        case 4:  // print_string
            this->out << &this->at<char>(this->regs[4]);
            break;
        case 5:  // read_int
            this->in >> (i32&)this->regs[2];
            break;
        case 8:  // read_string
            this->in.get(&this->at<char>(this->regs[4]), this->regs[5], '\0');
            break;
        case 9:  // sbrk
            this->regs[2] = this->heap_top;
            this->heap_top += this->regs[4];
            break;
        case 10:  // exit
            EXIT(0);
        case 11:  // print_char
            this->out << (char)this->regs[4];
            break;
        case 12:  // read_char
            this->in >> (char&)this->regs[2];
            break;
        case 13:  // open
            this->regs[2] = open(&this->at<char>(this->regs[4]), this->regs[5], this->regs[6]);
            break;
        case 14:  // read
            this->regs[2] = read(this->regs[4], &this->at<char>(this->regs[5]), this->regs[6]);
            break;
        case 15:  // write
            this->regs[2] = write(this->regs[4], &this->at<char>(this->regs[5]), this->regs[6]);
            break;
        case 16:  // close
            close(this->regs[4]);
            break;
        case 17:  // exit2
            EXIT(this->regs[4]);
        default:
            TRAP("syscall");
        }
    }

    void exec();
};

template<size_t... Seps>
constexpr auto explode(u32 instr) noexcept {
    return []<size_t... Is>(std::index_sequence<Is...>, u32 instr) {
        constexpr u32 seps[] = {32, Seps..., 0};
        return std::array{((instr >> seps[Is + 1]) & ((1u << (seps[Is] - seps[Is + 1])) - 1))...};
    }
    (std::make_index_sequence<sizeof...(Seps) + 1>{}, instr);
}

using DealFn = void (*)(Simulator&, u32);

// Heavily rely on compiler removing useless operations.

#define DEAL_R(func_body)                                                                        \
    [](Simulator& prog, u32 instr) {                                                             \
        [[maybe_unused]] auto [op, rs, rt, rd, shamt, func] = explode<26, 21, 16, 11, 6>(instr); \
        [[maybe_unused]] auto& reg_rs = prog.regs[rs];                                           \
        [[maybe_unused]] auto& reg_rt = prog.regs[rt];                                           \
        [[maybe_unused]] auto& reg_rd = prog.regs[rd];                                           \
        [[maybe_unused]] auto& reg_hi = prog.hi;                                                 \
        [[maybe_unused]] auto& reg_lo = prog.lo;                                                 \
        [[maybe_unused]] auto& pc = prog.pc;                                                     \
        func_body                                                                                \
    }

#define DEAL_I(func_body)                                                     \
    [](Simulator& prog, u32 instr) {                                          \
        [[maybe_unused]] auto [op, rs, rt, imm] = explode<26, 21, 16>(instr); \
        [[maybe_unused]] auto& reg_rs = prog.regs[rs];                        \
        [[maybe_unused]] auto& reg_rt = prog.regs[rt];                        \
        [[maybe_unused]] auto& pc = prog.pc;                                  \
        func_body                                                             \
    }

#define DEAL_J(func_body)                                     \
    [](Simulator& prog, u32 instr) {                          \
        [[maybe_unused]] auto [op, imm] = explode<26>(instr); \
        [[maybe_unused]] auto& pc = prog.pc;                  \
        func_body                                             \
    }

inline const std::unordered_map<u32, DealFn> op_0x00_map = {
    {0x20, DEAL_R({  // add
         if (__builtin_add_overflow((i32)reg_rs, (i32)reg_rt, (i32*)&reg_rd)) TRAP("add");
     })},
    {0x21, DEAL_R({  // addu
         reg_rd = reg_rs + reg_rt;
     })},
    {0x24, DEAL_R({  // and
         reg_rd = reg_rs & reg_rt;
     })},
    {0x1a, DEAL_R({  // div
         reg_lo = (i32)reg_rs / (i32)reg_rt;
         reg_hi = (i32)reg_rs % (i32)reg_rt;
     })},
    {0x1b, DEAL_R({  // divu
         reg_lo = reg_rs / reg_rt;
         reg_hi = reg_rs % reg_rt;
     })},
    {0x18, DEAL_R({  // mult
         u64 temp = (u64)(i32)reg_rs * (u64)(i32)reg_rt;
         reg_lo = temp;
         reg_hi = temp >> 32;
     })},
    {0x19, DEAL_R({  // multu
         u64 temp = (u64)reg_rs * (u64)reg_rt;
         reg_lo = temp;
         reg_hi = temp >> 32;
     })},
    {0x27, DEAL_R({  // nor
         reg_rd = ~(reg_rs | reg_rt);
     })},
    {0x25, DEAL_R({  // or
         reg_rd = reg_rs | reg_rt;
     })},
    {0x00, DEAL_R({  // sll
         reg_rd = reg_rt << shamt;
     })},
    {0x04, DEAL_R({  // sllv
         reg_rd = reg_rt << (reg_rs & 0b11111);
     })},
    {0x03, DEAL_R({  // sra
         reg_rd = (i32)reg_rt >> shamt;
     })},
    {0x07, DEAL_R({  // srav
         reg_rd = (i32)reg_rt >> (reg_rs & 0b11111);
     })},
    {0x02, DEAL_R({  // srl
         reg_rd = reg_rt >> shamt;
     })},
    {0x06, DEAL_R({  // srlv
         reg_rd = reg_rt >> (reg_rs & 0b11111);
     })},
    {0x22, DEAL_R({  // sub
         if (__builtin_sub_overflow((i32)reg_rs, (i32)reg_rt, (i32*)&reg_rd)) TRAP("sub");
     })},
    {0x23, DEAL_R({  // subu
         reg_rd = reg_rs - reg_rt;
     })},
    {0x26, DEAL_R({  // xor
         reg_rd = reg_rs ^ reg_rt;
     })},
    {0x2a, DEAL_R({  // slt
         reg_rd = (i32)reg_rs < (i32)reg_rt ? 1 : 0;
     })},
    {0x2b, DEAL_R({  // sltu
         reg_rd = reg_rs < reg_rt ? 1 : 0;
     })},
    {0x09, DEAL_R({  // jalr
         reg_rd = pc;
         pc = reg_rs;
     })},
    {0x08, DEAL_R({  // jr
         pc = reg_rs;
     })},
    {0x34, DEAL_R({  // teq
         if (reg_rs == reg_rt) TRAP("teq");
     })},
    {0x36, DEAL_R({  // tne
         if (reg_rs != reg_rt) TRAP("tne");
     })},
    {0x30, DEAL_R({  // tge
         if ((i32)reg_rs >= (i32)reg_rt) TRAP("tge");
     })},
    {0x31, DEAL_R({  // tgeu
         if (reg_rs >= reg_rt) TRAP("tgeu");
     })},
    {0x32, DEAL_R({  // tlt
         if ((i32)reg_rs < (i32)reg_rt) TRAP("tlt");
     })},
    {0x33, DEAL_R({  // tltu
         if (reg_rs < reg_rt) TRAP("tltu");
     })},
    {0x10, DEAL_R({  // mfhi
         reg_rd = reg_hi;
     })},
    {0x12, DEAL_R({  // mflo
         reg_rd = reg_lo;
     })},
    {0x11, DEAL_R({  // mthi
         reg_hi = reg_rs;
     })},
    {0x13, DEAL_R({  // mtlo
         reg_lo = reg_rs;
     })},
    {0x0c, DEAL_R({  // syscall
         prog.syscall();
     })},
};

inline const std::unordered_map<u32, DealFn> op_0x1c_map = {
    {0x21, DEAL_R({  // clo
         reg_rd = std::countl_one(reg_rs);
     })},
    {0x20, DEAL_R({  // clz
         reg_rd = std::countl_zero(reg_rs);
     })},
    {0x02, DEAL_R({  // mul
         reg_rd = reg_rs * reg_rt;
     })},
    {0x00, DEAL_R({  // madd
         u64 hilo = ((u64)reg_hi << 32u) | (u64)reg_lo;
         u64 temp = hilo + (u64)(i32)reg_rs * (u64)(i32)reg_rt;
         reg_lo = temp;
         reg_hi = temp >> 32;
     })},
    {0x01, DEAL_R({  // maddu
         u64 hilo = ((u64)reg_hi << 32u) | (u64)reg_lo;
         u64 temp = hilo + (u64)reg_rs * (u64)reg_rt;
         reg_lo = temp;
         reg_hi = temp >> 32;
     })},
    {0x04, DEAL_R({  // msub
         u64 hilo = ((u64)reg_hi << 32u) | (u64)reg_lo;
         u64 temp = hilo - (u64)(i32)reg_rs * (u64)(i32)reg_rt;
         reg_lo = temp;
         reg_hi = temp >> 32;
     })},
    {0x05, DEAL_R({  // msubu
         u64 hilo = ((u64)reg_hi << 32u) | (u64)reg_lo;
         u64 temp = hilo - (u64)reg_rs * (u64)reg_rt;
         reg_lo = temp;
         reg_hi = temp >> 32;
     })},
};

inline const std::unordered_map<u32, DealFn> op_0x01_map = {
    {0x01, DEAL_I({  // bgez
         if ((i32)reg_rs >= 0) pc += (u32)(i16)imm << 2u;
     })},
    {0x11, DEAL_I({  // bgezal
         prog.regs[31] = pc;
         if ((i32)reg_rs >= 0) pc += (u32)(i16)imm << 2u;
     })},
    {0x10, DEAL_I({  // bltzal
         prog.regs[31] = pc;
         if ((i32)reg_rs < 0) pc += (u32)(i16)imm << 2u;
     })},
    {0x00, DEAL_I({  // bltz
         if ((i32)reg_rs < 0) pc += (u32)(i16)imm << 2u;
     })},
    {0x0c, DEAL_I({  // teqi
         if (reg_rs == (u32)(i16)imm) TRAP("teqi");
     })},
    {0x0e, DEAL_I({  // tnei
         if (reg_rs != (u32)(i16)imm) TRAP("tnei");
     })},
    {0x08, DEAL_I({  // tgei
         if ((i32)reg_rs >= (i32)(i16)imm) TRAP("tgei");
     })},
    {0x09, DEAL_I({  // tgeiu
         if (reg_rs >= (u32)(i16)imm) TRAP("tgeiu");
     })},
    {0x0a, DEAL_I({  // tlti
         if ((i32)reg_rs < (i32)(i16)imm) TRAP("tlti");
     })},
    {0x0b, DEAL_I({  // tltiu
         if (reg_rs < (u32)(i16)imm) TRAP("tltiu");
     })},
};

inline const std::unordered_map<u32, DealFn> op_map = {
    {0x08, DEAL_I({  // addi
         if (__builtin_add_overflow((i32)reg_rs, (i32)(i16)imm, (i32*)&reg_rt)) TRAP("addi");
     })},
    {0x09, DEAL_I({  // addiu
         reg_rt = reg_rs + (i16)imm;
     })},
    {0x0c, DEAL_I({  // andi
         reg_rt = reg_rs & imm;
     })},
    {0x0d, DEAL_I({  // ori
         reg_rt = reg_rs | imm;
     })},
    {0x0e, DEAL_I({  // xori
         reg_rt = reg_rs ^ imm;
     })},
    {0x0f, DEAL_I({  // lui
         reg_rt = imm << 16u;
     })},
    {0x0a, DEAL_I({  // slti
         reg_rt = (i32)reg_rs < (i32)(i16)imm ? 1 : 0;
     })},
    {0x0b, DEAL_I({  // sltiu
         reg_rt = reg_rs < (u32)(i16)imm ? 1 : 0;
     })},
    {0x04, DEAL_I({  // beq
         if (reg_rs == reg_rt) pc += (u32)(i16)imm << 2u;
     })},
    {0x07, DEAL_I({  // bgtz
         if ((i32)reg_rs > 0) pc += (u32)(i16)imm << 2u;
     })},
    {0x06, DEAL_I({  // blez
         if ((i32)reg_rs <= 0) pc += (u32)(i16)imm << 2u;
     })},
    {0x05, DEAL_I({  // bne
         if (reg_rs != reg_rt) pc += (u32)(i16)imm << 2u;
     })},
    {0x02, DEAL_J({  // j
         pc = (pc & 0xf0000000) | (imm << 2u);
     })},
    {0x03, DEAL_J({  // jal
         prog.regs[31] = pc;
         pc = (pc & 0xf0000000) | (imm << 2u);
     })},
    {0x20, DEAL_I({  // lb
         reg_rt = prog.at<i8>(reg_rs + (i16)imm);
     })},
    {0x24, DEAL_I({  // lbu
         reg_rt = prog.at<u8>(reg_rs + (i16)imm);
     })},
    {0x21, DEAL_I({  // lh
         reg_rt = prog.at<i16>(reg_rs + (i16)imm);
     })},
    {0x25, DEAL_I({  // lhu
         reg_rt = prog.at<u16>(reg_rs + (i16)imm);
     })},
    {0x23, DEAL_I({  // lw
         reg_rt = prog.at<u32>(reg_rs + (i16)imm);
     })},
    {0x22, DEAL_I({  // lwl
         u32 addr = reg_rs + (i16)imm;
         u32 shift = 24 - 8 * (addr & 0b11);
         (reg_rt &= ~(~0u << shift)) |= (prog.at<u32>(addr & ~0b11) << shift);
     })},
    {0x26, DEAL_I({  // lwr
         u32 addr = reg_rs + (i16)imm;
         u32 shift = 8 * (addr & 0b11);
         (reg_rt &= ~(~0u >> shift)) |= (prog.at<u32>(addr & ~0b11) >> shift);
     })},
    {0x30, DEAL_I({  // ll
         reg_rt = prog.at<u32>(reg_rs + (i16)imm);
     })},
    {0x28, DEAL_I({  // sb
         prog.at<u32>(reg_rs + (i16)imm) = (u8)reg_rt;
     })},
    {0x29, DEAL_I({  // sh
         prog.at<u32>(reg_rs + (i16)imm) = (u16)reg_rt;
     })},
    {0x2b, DEAL_I({  // sw
         prog.at<u32>(reg_rs + (i16)imm) = reg_rt;
     })},
    {0x2a, DEAL_I({  // swl
         u32 addr = reg_rs + (i16)imm;
         u32 shift = 24 - 8 * (addr & 0b11);
         (prog.at<u32>(addr & ~0b11) &= ~(~0u >> shift)) |= (reg_rt >> shift);
     })},
    {0x2e, DEAL_I({  // swr
         u32 addr = reg_rs + (i16)imm;
         u32 shift = 8 * (addr & 0b11);
         (prog.at<u32>(addr & ~0b11) &= ~(~0u << shift)) |= (reg_rt << shift);
     })},
    {0x38, DEAL_I({  // sc
         prog.at<u32>(reg_rs + (i16)imm) = reg_rt;
     })},
};

inline void Simulator::exec() {
    while (this->pc < this->text_end) {
        u32 instr = this->at<u32>(this->pc);
        this->pc += 4;
        u32 op = (instr >> 26u) & 0x3f;
        switch (op) {
        case 0x00:
            op_0x00_map.at(instr & 0x3f)(*this, instr);
            break;
        case 0x1c:
            op_0x1c_map.at(instr & 0x3f)(*this, instr);
            break;
        case 0x01:
            op_0x01_map.at((instr >> 16u) & 0x1f)(*this, instr);
            break;
        default:
            op_map.at(op)(*this, instr);
            break;
        }
    }
}

inline void simulate(std::istream& in, std::ostream& out, Memory mem, u32 text_end) {
    Simulator(in, out, std::move(mem), text_end).exec();
}

#undef DEAL_R
#undef DEAL_I
#undef DEAL_J
#undef TRAP
#undef EXIT
