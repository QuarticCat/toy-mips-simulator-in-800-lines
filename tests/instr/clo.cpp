#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, clo_1,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, clo_2,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32"
);

SIM_TEST(Instr, clo_3,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, clo_4,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, clo_5,
    R"(
      .text
        lui $t0, 255
        ori $t0, $t0, 255  # $t0 = 0x00FF00FF
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, clo_6,
    R"(
      .text
        lui $t0, 65280
        ori $t0, $t0, 65280  # $t0 = 0xFF00FF00
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "8"
);

SIM_TEST(Instr, clo_7,
    R"(
      .text
        ori $t0, $zero, 65535  # $t0 = 0x0000FFFF
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, clo_8,
    R"(
      .text
        lui $t0, 65535  # $t0 = 0xFFFF0000
        clo $a0, $t0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "16"
);

// clang-format on
