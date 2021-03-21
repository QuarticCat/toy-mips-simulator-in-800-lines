#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, jal_1,
    R"(
      .text
        jal a
        ori $a0, $zero, 1
      a:
        ori $a0, $zero, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, jal_2,
    R"(
      .text
        jal 1048578        # jal a
        ori $a0, $zero, 1
        ori $a0, $zero, 2  # label: a
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, jal_3,
    R"(
      .text
        addu $a0, $zero, $zero
        jal a
        addiu $a0, $a0, 1
      b:
        addiu $a0, $a0, 2
        jal c
      a:
        addiu $a0, $a0, 3
        jal b
      c:
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "5"
);

SIM_TEST(Instr, jal_4,
    R"(
      .text
        addu $a0, $zero, $zero
        jal 1048581        # jal a
        addiu $a0, $a0, 1
        addiu $a0, $a0, 2  # label: b
        jal 1048583        # jal c
        addiu $a0, $a0, 3  # label: a
        jal 1048579        # jal b
        ori $v0, $zero, 1  # label: c
        syscall
    )",
    "",
    "5"
);

// clang-format on
