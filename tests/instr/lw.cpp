#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, lw_1,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lw $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lw_2,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lw $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lw_3,
    R"(
      .data
        .word 1
        .word 2
        .word 3
        .word 4
      .text
        lui $t0, 80  # base address
        lw $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lw_4,
    R"(
      .data
        .byte 1, 2, 3, 4, 5, 6, 7
      .text
        lui $t0, 80  # base address
        lw $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "67305985"
);

SIM_TEST(Instr, lw_5,
    R"(
      .data
        .byte 1, 2, 3
        .byte 4, 5, 6, 7
        .byte 8, 9, 10
      .text
        lui $t0, 80  # base address
        lw $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "117835012"
);

SIM_TEST(Instr, lw_6,
    R"(
      .data
        .half 1, 2, 3
      .text
        lui $t0, 80  # base address
        lw $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "131073"
);

SIM_TEST(Instr, lw_7,
    R"(
      .data
        .half 1
        .half 2, 3
        .half 4
      .text
        lui $t0, 80  # base address
        lw $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "196610"
);

SIM_TEST(Instr, lw_8,
    R"(
      .data
        .ascii "ABCDEFG"
      .text
        lui $t0, 80  # base address
        lw $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1145258561"
);

SIM_TEST(Instr, lw_9,
    R"(
      .data
        .ascii "ABC"
        .ascii "DEFG"
        .ascii "HIJ"
      .text
        lui $t0, 80  # base address
        lw $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1195787588"
);

SIM_TEST(Instr, lw_10,
    R"(
      .data
        .asciiz "ABC"
      .text
        lui $t0, 80  # base address
        lw $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4407873"
);

SIM_TEST(Instr, lw_11,
    R"(
      .data
        .asciiz "AB"
        .asciiz "CDE"
        .asciiz "FG"
      .text
        lui $t0, 80  # base address
        lw $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4539459"
);

SIM_TEST(Instr, lw_12,
    R"(
      .text
        lui $t0, 64  # base address
        lw $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1007157312"  // 001111'00000'01000'0000000001000000
);

SIM_TEST(Instr, lw_13,
    R"(
      .text
        lui $t0, 64  # base address
        lw $a0, 4($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1929117692"  // 100011'01000'00100'0000000000000100
);

// clang-format on
