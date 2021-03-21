#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, print_int_1,
    R"(
      .text
        lui $a0, 32768  # $t0 = -2147483648
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, print_int_2,
    R"(
      .text
        lui $a0, 65535
        ori $a0, $a0, 65534  # $a0 = -2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"
);

SIM_TEST(Instr, print_int_3,
    R"(
      .text
        lui $a0, 65535
        ori $a0, $a0, 65535  # $t0 = -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, print_int_4,
    R"(
      .text
        addu $a0, $zero, $zero  # $a0 = 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, print_int_5,
    R"(
      .text
        ori $a0, $zero, 1  # $a0 = 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, print_int_6,
    R"(
      .text
        ori $a0, $zero, 2  # $a0 = 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, print_int_7,
    R"(
      .text
        lui $a0, 32767
        ori $a0, $a0, 65535  # $a0 = 2147483647
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

// clang-format on
