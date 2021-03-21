#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, lwr_1,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "LKJI"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwr $t1, 0($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwr_2,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "KJIe"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwr $t1, 1($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwr_3,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "JIfe"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwr $t1, 2($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwr_4,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "Igfe"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwr $t1, 3($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwr_5,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwr $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lwr_6,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwr $a0, 3($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "305419776"
);

SIM_TEST(Instr, lwr_7,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwr $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lwr_8,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwr $a0, 11($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "305419776"
);

// clang-format on
