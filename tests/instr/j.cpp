#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, j_1,
    R"(
      .text
        j a
        ori $a0, $zero, 1
      a:
        ori $a0, $zero, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, j_2,
    R"(
      .text
        j 1048578          # j a
        ori $a0, $zero, 1
        ori $a0, $zero, 2  # label: a
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, j_3,
    R"(
      .text
        addu $a0, $zero, $zero
        j a
        addiu $a0, $a0, 1
      b:
        addiu $a0, $a0, 2
        j c
      a:
        addiu $a0, $a0, 3
        j b
      c:
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "5"
);

SIM_TEST(Instr, j_4,
    R"(
      .text
        addu $a0, $zero, $zero
        j 1048581          # j a
        addiu $a0, $a0, 1
        addiu $a0, $a0, 2  # label: b
        j 1048583          # j c
        addiu $a0, $a0, 3  # label: a
        j 1048579          # j b
        ori $v0, $zero, 1  # label: c
        syscall
    )",
    "",
    "5"
);

// clang-format on
