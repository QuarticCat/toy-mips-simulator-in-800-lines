#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, sltu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltu_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 1  # $t1 = 1
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltu_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 2  # $t1 = 2
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltu_4,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltu_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 32768       # $t1 = 2147483648
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltu_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535     # $t0 = 4294967295
        addu $t1, $zero, $zero  # $t1 = 0
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltu_7,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        lui $t1, 65535
        ori $t1, $t1, 65535     # $t1 = 4294967295
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltu_8,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        ori $t1, $zero, 1       # $t1 = 1
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltu_9,
    R"(
      .text
        ori $t0, $zero, 1       # $t0 = 1
        addu $t1, $zero, $zero  # $t1 = 0
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltu_10,
    R"(
      .text
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltu_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 1    # $t1 = 1
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltu_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = 2147483648
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltu_13,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        sltu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

// clang-format on
