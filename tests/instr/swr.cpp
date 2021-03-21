#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, swr_1,
    R"(
      .data
        .ascii "lkji"  # memory
        .ascii "HGFE"  # register
        .ascii "HGFE"
      .text
        lui $t0, 80  # base address
        lw $t2, 4($t0)
        swr $t2, 0($t0)
        lw $t2, 0($t0)
        lw $t3, 8($t0)
        xor $a0, $t2, $t3
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, swr_2,
    R"(
      .data
        .ascii "lkji"  # memory
        .ascii "HGFE"  # register
        .ascii "lHGF"
      .text
        lui $t0, 80  # base address
        lw $t2, 4($t0)
        swr $t2, 1($t0)
        lw $t2, 0($t0)
        lw $t3, 8($t0)
        xor $a0, $t2, $t3
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, swr_3,
    R"(
      .data
        .ascii "lkji"  # memory
        .ascii "HGFE"  # register
        .ascii "lkHG"
      .text
        lui $t0, 80  # base address
        lw $t2, 4($t0)
        swr $t2, 2($t0)
        lw $t2, 0($t0)
        lw $t3, 8($t0)
        xor $a0, $t2, $t3
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, swr_4,
    R"(
      .data
        .ascii "lkji"  # memory
        .ascii "HGFE"  # register
        .ascii "lkjH"
      .text
        lui $t0, 80  # base address
        lw $t2, 4($t0)
        swr $t2, 3($t0)
        lw $t2, 0($t0)
        lw $t3, 8($t0)
        xor $a0, $t2, $t3
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

// clang-format on
