#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, lui_1,
    R"(
      .text
        lui $a0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, lui_2,
    R"(
      .text
        lui $a0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "65536"
);

SIM_TEST(Instr, lui_3,
    R"(
      .text
        lui $a0, 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147418112"
);

SIM_TEST(Instr, lui_4,
    R"(
      .text
        lui $a0, 32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, lui_5,
    R"(
      .text
        lui $a0, 65535
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"
);

// clang-format on
