#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, lb_1,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lb_2,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lb $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lb_3,
    R"(
      .data
        .word 1
        .word 2
        .word 3
        .word 4
      .text
        lui $t0, 80  # base address
        lb $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lb_4,
    R"(
      .data
        .byte 1
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lb_5,
    R"(
      .data
        .byte 129
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-127"
);

SIM_TEST(Instr, lb_6,
    R"(
      .data
        .byte 1, 2, 3, 4, 5, 6, 7
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);


SIM_TEST(Instr, lb_7,
    R"(
      .data
        .byte 129, 130, 131, 132, 133, 134, 135
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-127"
);

SIM_TEST(Instr, lb_8,
    R"(
      .data
        .byte 1, 2, 3
        .byte 4, 5, 6, 7
        .byte 8, 9, 10
      .text
        lui $t0, 80  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4"
);

SIM_TEST(Instr, lb_9,
    R"(
      .data
        .byte 129, 130, 131
        .byte 132, 133, 134, 135
        .byte 136, 137, 138
      .text
        lui $t0, 80  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-124"
);

SIM_TEST(Instr, lb_10,
    R"(
      .data
        .half 1
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lb_11,
    R"(
      .data
        .half 32769
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lb_12,
    R"(
      .data
        .half 1, 2, 3
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lb_13,
    R"(
      .data
        .half 32769, 32770, 32771
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lb_14,
    R"(
      .data
        .half 1
        .half 2, 3
        .half 4
      .text
        lui $t0, 80  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, lb_15,
    R"(
      .data
        .half 32769
        .half 32770, 32771
        .half 32772
      .text
        lui $t0, 80  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, lb_16,
    R"(
      .data
        .ascii "A"
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "65"
);

SIM_TEST(Instr, lb_17,
    R"(
      .data
        .ascii "ABCDEFG"
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "65"
);

SIM_TEST(Instr, lb_18,
    R"(
      .data
        .ascii "ABC"
        .ascii "DEFG"
        .ascii "HIJ"
      .text
        lui $t0, 80  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "68"
);

SIM_TEST(Instr, lb_19,
    R"(
      .data
        .asciiz "ABC"
      .text
        lui $t0, 80  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "65"
);

SIM_TEST(Instr, lb_20,
    R"(
      .data
        .asciiz "AB"
        .asciiz "CDE"
        .asciiz "FG"
      .text
        lui $t0, 80  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "67"
);

SIM_TEST(Instr, lb_21,
    R"(
      .text
        lui $t0, 64  # base address
        lb $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "64"  // 001111'00000'01000'00000000[01000000]
);

SIM_TEST(Instr, lb_22,
    R"(
      .text
        lui $t0, 64  # base address
        lb $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4"  // 100000'01000'00100'000[000000100]
);

SIM_TEST(Instr, lb_23,
    R"(
      .text
        lui $t0, 64  # base address
        lb $a0, 7($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-127"  // [100000'01]000'00100'000000000111
);

// clang-format on
