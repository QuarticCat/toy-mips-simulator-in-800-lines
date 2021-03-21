#pragma once

#include <array>
#include <unordered_map>

#include "def.hpp"

enum /* class */ Arg : u8 {  // numbers represent offsets
    RS = 21,
    RT = 16,
    RD = 11,
    SA = 6,  // shift amount
    IM = 0,  // immediate or label
    NO = 31,  // can be any # < 32
};

enum class Type : u8 { R, I, J };

struct Instr {
    const u32 pattern;
    const std::array<u8, 3> offsets;
    const Type type;

    /// Generate instruction binary by given arguments.
    /// Caller should ensure that used args are valid and unused args are zero.
    [[nodiscard]] u32 gen(std::array<u32, 3> args) const noexcept {
        auto ret = this->pattern;
        for (size_t i: {0, 1, 2}) ret |= args[i] << this->offsets[i];
        return ret;
    }
};

/// `sp` is `func` for R-type and `rt` for I-type.
consteval Instr make_instr(u32 op, u32 sp, std::array<u8, 3> arg_order, Type type) noexcept {
    switch (type) {
    case Type::R:
        return {op << 26u | sp, arg_order, type};
    case Type::I:
        return {op << 26u | sp << 16u, arg_order, type};
    case Type::J:
        return {op << 26u, arg_order, type};
    }
}

// clang-format off
inline const std::unordered_map<Token, Instr> instr_map = {
    {"add",     make_instr(0x00, 0x20, {RD, RS, RT}, Type::R)},
    {"addu",    make_instr(0x00, 0x21, {RD, RS, RT}, Type::R)},
    {"addi",    make_instr(0x08, 0x00, {RT, RS, IM}, Type::I)},
    {"addiu",   make_instr(0x09, 0x00, {RT, RS, IM}, Type::I)},
    {"and",     make_instr(0x00, 0x24, {RD, RS, RT}, Type::R)},
    {"andi",    make_instr(0x0c, 0x00, {RT, RS, IM}, Type::I)},
    {"clo",     make_instr(0x1c, 0x21, {RD, RS, NO}, Type::R)},
    {"clz",     make_instr(0x1c, 0x20, {RD, RS, NO}, Type::R)},
    {"div",     make_instr(0x00, 0x1a, {RS, RT, NO}, Type::R)},
    {"divu",    make_instr(0x00, 0x1b, {RS, RT, NO}, Type::R)},
    {"mult",    make_instr(0x00, 0x18, {RS, RT, NO}, Type::R)},
    {"multu",   make_instr(0x00, 0x19, {RS, RT, NO}, Type::R)},
    {"mul",     make_instr(0x1c, 0x02, {RD, RS, RT}, Type::R)},
    {"madd",    make_instr(0x1c, 0x00, {RS, RT, NO}, Type::R)},
    {"maddu",   make_instr(0x1c, 0x01, {RS, RT, NO}, Type::R)},
    {"msub",    make_instr(0x1c, 0x04, {RS, RT, NO}, Type::R)},
    {"msubu",   make_instr(0x1c, 0x05, {RS, RT, NO}, Type::R)},
    {"nor",     make_instr(0x00, 0x27, {RD, RS, RT}, Type::R)},
    {"or",      make_instr(0x00, 0x25, {RD, RS, RT}, Type::R)},
    {"ori",     make_instr(0x0d, 0x00, {RT, RS, IM}, Type::I)},
    {"sll",     make_instr(0x00, 0x00, {RD, RT, SA}, Type::R)},
    {"sllv",    make_instr(0x00, 0x04, {RD, RT, RS}, Type::R)},
    {"sra",     make_instr(0x00, 0x03, {RD, RT, SA}, Type::R)},
    {"srav",    make_instr(0x00, 0x07, {RD, RT, RS}, Type::R)},
    {"srl",     make_instr(0x00, 0x02, {RD, RT, SA}, Type::R)},
    {"srlv",    make_instr(0x00, 0x06, {RD, RT, RS}, Type::R)},
    {"sub",     make_instr(0x00, 0x22, {RD, RS, RT}, Type::R)},
    {"subu",    make_instr(0x00, 0x23, {RD, RS, RT}, Type::R)},
    {"xor",     make_instr(0x00, 0x26, {RD, RS, RT}, Type::R)},
    {"xori",    make_instr(0x0e, 0x00, {RT, RS, IM}, Type::I)},
    {"lui",     make_instr(0x0f, 0x00, {RT, IM, NO}, Type::I)},
    {"slt",     make_instr(0x00, 0x2a, {RD, RS, RT}, Type::R)},
    {"sltu",    make_instr(0x00, 0x2b, {RD, RS, RT}, Type::R)},
    {"slti",    make_instr(0x0a, 0x00, {RT, RS, IM}, Type::I)},
    {"sltiu",   make_instr(0x0b, 0x00, {RT, RS, IM}, Type::I)},
    {"beq",     make_instr(0x04, 0x00, {RS, RT, IM}, Type::I)},
    {"bgez",    make_instr(0x01, 0x01, {RS, IM, NO}, Type::I)},
    {"bgezal",  make_instr(0x01, 0x11, {RS, IM, NO}, Type::I)},
    {"bgtz",    make_instr(0x07, 0x00, {RS, IM, NO}, Type::I)},
    {"blez",    make_instr(0x06, 0x00, {RS, IM, NO}, Type::I)},
    {"bltzal",  make_instr(0x01, 0x10, {RS, IM, NO}, Type::I)},
    {"bltz",    make_instr(0x01, 0x00, {RS, IM, NO}, Type::I)},
    {"bne",     make_instr(0x05, 0x00, {RS, RT, IM}, Type::I)},
    {"j",       make_instr(0x02, 0x00, {IM, NO, NO}, Type::J)},
    {"jal",     make_instr(0x03, 0x00, {IM, NO, NO}, Type::J)},
    {"jalr",    make_instr(0x00, 0x09, {RS, RD, NO}, Type::R)},
    {"jr",      make_instr(0x00, 0x08, {RS, NO, NO}, Type::R)},
    {"teq",     make_instr(0x00, 0x34, {RS, RT, NO}, Type::R)},
    {"teqi",    make_instr(0x01, 0x0c, {RS, IM, NO}, Type::I)},
    {"tne",     make_instr(0x00, 0x36, {RS, RT, NO}, Type::R)},
    {"tnei",    make_instr(0x01, 0x0e, {RS, IM, NO}, Type::I)},
    {"tge",     make_instr(0x00, 0x30, {RS, RT, NO}, Type::R)},
    {"tgeu",    make_instr(0x00, 0x31, {RS, RT, NO}, Type::R)},
    {"tgei",    make_instr(0x01, 0x08, {RS, IM, NO}, Type::I)},
    {"tgeiu",   make_instr(0x01, 0x09, {RS, IM, NO}, Type::I)},
    {"tlt",     make_instr(0x00, 0x32, {RS, RT, NO}, Type::R)},
    {"tltu",    make_instr(0x00, 0x33, {RS, RT, NO}, Type::R)},
    {"tlti",    make_instr(0x01, 0x0a, {RS, IM, NO}, Type::I)},
    {"tltiu",   make_instr(0x01, 0x0b, {RS, IM, NO}, Type::I)},
    {"lb",      make_instr(0x20, 0x00, {RT, IM, RS}, Type::I)},
    {"lbu",     make_instr(0x24, 0x00, {RT, IM, RS}, Type::I)},
    {"lh",      make_instr(0x21, 0x00, {RT, IM, RS}, Type::I)},
    {"lhu",     make_instr(0x25, 0x00, {RT, IM, RS}, Type::I)},
    {"lw",      make_instr(0x23, 0x00, {RT, IM, RS}, Type::I)},
    {"lwl",     make_instr(0x22, 0x00, {RT, IM, RS}, Type::I)},
    {"lwr",     make_instr(0x26, 0x00, {RT, IM, RS}, Type::I)},
    {"ll",      make_instr(0x30, 0x00, {RT, IM, RS}, Type::I)},
    {"sb",      make_instr(0x28, 0x00, {RT, IM, RS}, Type::I)},
    {"sh",      make_instr(0x29, 0x00, {RT, IM, RS}, Type::I)},
    {"sw",      make_instr(0x2b, 0x00, {RT, IM, RS}, Type::I)},
    {"swl",     make_instr(0x2a, 0x00, {RT, IM, RS}, Type::I)},
    {"swr",     make_instr(0x2e, 0x00, {RT, IM, RS}, Type::I)},
    {"sc",      make_instr(0x38, 0x00, {RT, IM, RS}, Type::I)},
    {"mfhi",    make_instr(0x00, 0x10, {RD, NO, NO}, Type::R)},
    {"mflo",    make_instr(0x00, 0x12, {RD, NO, NO}, Type::R)},
    {"mthi",    make_instr(0x00, 0x11, {RS, NO, NO}, Type::R)},
    {"mtlo",    make_instr(0x00, 0x13, {RS, NO, NO}, Type::R)},
    {"syscall", make_instr(0x00, 0x0c, {NO, NO, NO}, Type::R)},
};
// clang-format on
