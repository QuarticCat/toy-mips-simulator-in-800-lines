#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, srl_1,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        srl $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srl_2,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        srl $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srl_3,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        srl $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srl_4,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        srl $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srl_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        srl $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srl_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        srl $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, srl_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        srl $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "65535"  // 0x0000FFFF
);

SIM_TEST(Instr, srl_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        srl $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"  // 0x00000001
);

SIM_TEST(Instr, srl_9,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        srl $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, srl_10,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        srl $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1073741823"  // 0x3FFFFFFF
);

SIM_TEST(Instr, srl_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        srl $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32767"  // 0x00007FFFF
);

SIM_TEST(Instr, srl_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        srl $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srl_13,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        srl $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, srl_14,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        srl $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1073741824"  // 0x40000000
);

SIM_TEST(Instr, srl_15,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        srl $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32768"  // 0x00008000
);

SIM_TEST(Instr, srl_16,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        srl $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"  // 0x00000001
);

// clang-format on
