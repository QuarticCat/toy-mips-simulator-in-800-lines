#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, exit_1,
    R"(
      .text
        ori $v0, $zero, 10
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, exit_2,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
        ori $v0, $zero, 10
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, exit_3,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
        ori $v0, $zero, 10
        syscall
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
