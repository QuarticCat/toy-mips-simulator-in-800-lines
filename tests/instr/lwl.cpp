#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, lwl_1,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "hgfL"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwl $t1, 0($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwl_2,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "hgLK"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwl $t1, 1($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwl_3,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "hLKJ"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwl $t1, 2($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwl_4,
    R"(
      .data
        .ascii "LKJI"  # memory
        .ascii "hgfe"  # register
        .ascii "LKJI"
      .text
        lui $t0, 80  # base address
        lw $t1, 4($t0)
        lwl $t1, 3($t0)
        lw $t2, 8($t0)
        xor $a0, $t1, $t2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lwl_5,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwl $a0, 3($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, lwl_6,
    R"(
      .data
        .word 1
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwl $a0, 0($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "20207224"
);

SIM_TEST(Instr, lwl_7,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwl $a0, 11($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, lwl_8,
    R"(
      .data
        .word 1, 2, 3, 4
      .text
        lui $t0, 80  # base address
        lui $a0, 4660
        ori $a0, $a0, 22136  # $a0 = 0x12345678
        lwl $a0, 8($t0)
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "53761656"
);

// clang-format on
