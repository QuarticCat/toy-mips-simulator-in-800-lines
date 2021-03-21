#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, sra_1,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sra $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sra_2,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sra $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sra_3,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sra $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sra_4,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        sra $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sra_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sra $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sra_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sra $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sra_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sra $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sra_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        sra $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sra_9,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sra $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, sra_10,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sra $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1073741823"  // 0x3FFFFFFF
);

SIM_TEST(Instr, sra_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sra $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32767"  // 0x00007FFFF
);

SIM_TEST(Instr, sra_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        sra $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sra_13,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sra $a0, $t0, 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sra_14,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sra $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1073741824"  // 0xC0000000
);

SIM_TEST(Instr, sra_15,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sra $a0, $t0, 16
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-32768"  // 0xFFFF8000
);

SIM_TEST(Instr, sra_16,
    R"(
      .text
        lui $t0, 32768  # $t0 = 0x80000000
        sra $a0, $t0, 31
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

// clang-format on
