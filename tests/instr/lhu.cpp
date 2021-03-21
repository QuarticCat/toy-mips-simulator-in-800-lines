#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, lhu_1,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lhu_2,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lhu $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lhu_3,
    R"(
      .data
        .word 1
        .word 2
        .word 3
        .word 4
      .text
        lui $t0, 80  # base address
        lhu $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lhu_4,
    R"(
      .data
        .byte 1, 2
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "513"
);

SIM_TEST(Instr, lhu_5,
    R"(
      .data
        .byte 129, 130
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "33409"
);

SIM_TEST(Instr, lhu_6,
    R"(
      .data
        .byte 1, 2, 3, 4, 5, 6, 7
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "513"
);


SIM_TEST(Instr, lhu_7,
    R"(
      .data
        .byte 129, 130, 131, 132, 133, 134, 135
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "33409"
);

SIM_TEST(Instr, lhu_8,
    R"(
      .data
        .byte 1, 2, 3
        .byte 4, 5, 6, 7
        .byte 8, 9, 10
      .text
        lui $t0, 80  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1284"
);

SIM_TEST(Instr, lhu_9,
    R"(
      .data
        .byte 129, 130, 131
        .byte 132, 133, 134, 135
        .byte 136, 137, 138
      .text
        lui $t0, 80  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "34180"
);

SIM_TEST(Instr, lhu_10,
    R"(
      .data
        .half 1
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lhu_11,
    R"(
      .data
        .half 32769
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32769"
);

SIM_TEST(Instr, lhu_12,
    R"(
      .data
        .half 1, 2, 3
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lhu_13,
    R"(
      .data
        .half 32769, 32770, 32771
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32769"
);

SIM_TEST(Instr, lhu_14,
    R"(
      .data
        .half 1
        .half 2, 3
        .half 4
      .text
        lui $t0, 80  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, lhu_15,
    R"(
      .data
        .half 32769
        .half 32770, 32771
        .half 32772
      .text
        lui $t0, 80  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32770"
);

SIM_TEST(Instr, lhu_16,
    R"(
      .data
        .ascii "AB"
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "16961"
);

SIM_TEST(Instr, lhu_17,
    R"(
      .data
        .ascii "ABCDEFG"
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "16961"
);

SIM_TEST(Instr, lhu_18,
    R"(
      .data
        .ascii "ABC"
        .ascii "DEFG"
        .ascii "HIJ"
      .text
        lui $t0, 80  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "17732"
);

SIM_TEST(Instr, lhu_19,
    R"(
      .data
        .asciiz "A"
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "65"
);


SIM_TEST(Instr, lhu_20,
    R"(
      .data
        .asciiz "ABC"
      .text
        lui $t0, 80  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "16961"
);

SIM_TEST(Instr, lhu_21,
    R"(
      .data
        .asciiz "AB"
        .asciiz "CDE"
        .asciiz "FG"
      .text
        lui $t0, 80  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "17475"
);

SIM_TEST(Instr, lhu_22,
    R"(
      .text
        lui $t0, 64  # base address
        lhu $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "64"  // 001111'00000'01000'[0000000001000000]
);

SIM_TEST(Instr, lhu_23,
    R"(
      .text
        lui $t0, 64  # base address
        lhu $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4"  // 100101'01000'00100'[0000000000000100]
);

SIM_TEST(Instr, lhu_24,
    R"(
      .text
        lui $t0, 64  # base address
        lhu $a0, 6($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "38148"  // [100101'01000'00100]'0000000000000110
);

// clang-format on
