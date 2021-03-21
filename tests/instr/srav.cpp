#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, srav_1,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        addu $t1, $zero, $zero  # $t1 = 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_2,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 32      # $t1 = 32 <=> 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_3,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 1       # $t1 = 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_4,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 33      # $t1 = 33 <=> 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_5,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 16      # $t1 = 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_6,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        lui $t1, 21845
        ori $t1, $t1, 21840     # $t1 = 1431655760 <=> 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_7,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 31      # $t1 = 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_8,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        lui $t1, 65535
        ori $t1, $t1, 65535     # $t1 = -1 <=> 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_9,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535     # $t0 = 0xFFFFFFFF
        addu $t1, $zero, $zero  # $t1 = 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_10,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 32   # $t1 = 32 <=> 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_11,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 1    # $t1 = 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_12,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 33   # $t1 = 33 <=> 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 16   # $t1 = 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        lui $t1, 21845
        ori $t1, $t1, 21840  # $t1 = 1431655760 <=> 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 31   # $t1 = 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_16,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1 <=> 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_17,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535     # $t0 = 0x7FFFFFFF
        addu $t1, $zero, $zero  # $t1 = 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, srav_18,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 32   # $t1 = 32 <=> 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, srav_19,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 1    # $t1 = 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1073741823"  // 0x3FFFFFFF
);

SIM_TEST(Instr, srav_20,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 33   # $t1 = 33 <=> 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1073741823"  // 0x3FFFFFFF
);

SIM_TEST(Instr, srav_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 16   # $t1 = 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32767"  // 0x00007FFFF
);

SIM_TEST(Instr, srav_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        lui $t1, 21845
        ori $t1, $t1, 21840  # $t1 = 1431655760 <=> 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "32767"  // 0x00007FFFF
);

SIM_TEST(Instr, srav_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 31   # $t1 = 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_24,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1 <=> 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, srav_25,
    R"(
      .text
        lui $t0, 32768          # $t0 = 0x80000000
        addu $t1, $zero, $zero  # $t1 = 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, srav_26,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 32  # $t1 = 32 <=> 0
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, srav_27,
    R"(
      .text
        lui $t0, 32768     # $t0 = 0x80000000
        ori $t1, $zero, 1  # $t1 = 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1073741824"  // 0xC0000000
);

SIM_TEST(Instr, srav_28,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 33  # $t1 = 33 <=> 1
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1073741824"  // 0xC0000000
);

SIM_TEST(Instr, srav_29,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 16  # $t1 = 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-32768"  // 0xFFFF8000
);

SIM_TEST(Instr, srav_30,
    R"(
      .text
        lui $t0, 32768       # $t0 = 0x80000000
        lui $t1, 21845
        ori $t1, $t1, 21840  # $t1 = 1431655760 <=> 16
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-32768"  // 0xFFFF8000
);

SIM_TEST(Instr, srav_31,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 31  # $t1 = 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, srav_32,
    R"(
      .text
        lui $t0, 32768       # $t0 = 0x80000000
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1 <=> 31
        srav $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

// clang-format on
