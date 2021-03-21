#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, sll_1,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sll $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sll_2,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sll $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sll_3,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sll $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sll_4,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sll $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sll_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sll $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sll_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sll $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"  // 0xFFFFFFFE
);

SIM_TEST(Instr, sll_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sll $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"  // 0xFFFF0000
);

SIM_TEST(Instr, sll_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sll $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sll_9,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sll $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, sll_10,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sll $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"  // 0xFFFFFFFE
);

SIM_TEST(Instr, sll_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sll $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"  // 0xFFFF0000
);

SIM_TEST(Instr, sll_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sll $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sll_13,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sll $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sll_14,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sll $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sll_15,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sll $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sll_16,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sll $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

// clang-format on
