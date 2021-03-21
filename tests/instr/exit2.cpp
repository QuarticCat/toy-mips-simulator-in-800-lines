#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, exit2_1,
    R"(
      .text
        addu $a0, $zero, $zero
        ori $v0, $zero, 17
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, exit2_2,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
        addu $a0, $zero, $zero
        ori $v0, $zero, 17
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, exit2_3,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
        addu $a0, $zero, $zero
        ori $v0, $zero, 17
        syscall
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_EXIT_TEST(Instr, exit2_4,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 17
        syscall
    )",
    "",
    ""
);

SIM_EXIT_TEST(Instr, exit2_5,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 1
        ori $v0, $zero, 17
        syscall
    )",
    "",
    "1"
);

SIM_EXIT_TEST(Instr, exit2_6,
    R"(
      .text
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 1
        ori $v0, $zero, 17
        syscall
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
