#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, sllv_1,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        addu $t1, $zero, $zero  # $t1 = 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_2,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 32      # $t1 = 32 <=> 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_3,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 1       # $t1 = 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_4,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 33      # $t1 = 33 <=> 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_5,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 16      # $t1 = 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_6,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        lui $t1, 21845
        ori $t1, $t1, 21840     # $t1 = 1431655760 <=> 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_7,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        ori $t1, $zero, 31      # $t1 = 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_8,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0x00000000
        lui $t1, 65535
        ori $t1, $t1, 65535     # $t1 = -1 <=> 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_9,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535     # $t0 = 0xFFFFFFFF
        addu $t1, $zero, $zero  # $t1 = 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sllv_10,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 32   # $t1 = 32 <=> 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, sllv_11,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 1    # $t1 = 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"  // 0xFFFFFFFE
);

SIM_TEST(Instr, sllv_12,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 33   # $t1 = 33 <=> 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"  // 0xFFFFFFFE
);

SIM_TEST(Instr, sllv_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 16   # $t1 = 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"  // 0xFFFF0000
);

SIM_TEST(Instr, sllv_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        lui $t1, 21845
        ori $t1, $t1, 21840  # $t1 = 1431655760 <=> 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"  // 0xFFFF0000
);

SIM_TEST(Instr, sllv_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        ori $t1, $zero, 31   # $t1 = 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sllv_16,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 0xFFFFFFFF
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1 <=> 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sllv_17,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535     # $t0 = 0x7FFFFFFF
        addu $t1, $zero, $zero  # $t1 = 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, sllv_18,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 32   # $t1 = 32 <=> 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"  // 0x7FFFFFFF
);

SIM_TEST(Instr, sllv_19,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 1    # $t1 = 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"  // 0xFFFFFFFE
);

SIM_TEST(Instr, sllv_20,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 33   # $t1 = 33 <=> 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"  // 0xFFFFFFFE
);

SIM_TEST(Instr, sllv_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 16   # $t1 = 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"  // 0xFFFF0000
);

SIM_TEST(Instr, sllv_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        lui $t1, 21845
        ori $t1, $t1, 21840  # $t1 = 1431655760 <=> 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-65536"  // 0xFFFF0000
);

SIM_TEST(Instr, sllv_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        ori $t1, $zero, 31   # $t1 = 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sllv_24,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 0x7FFFFFFF
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1 <=> 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sllv_25,
    R"(
      .text
        lui $t0, 32768          # $t0 = 0x80000000
        addu $t1, $zero, $zero  # $t1 = 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sllv_26,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 32  # $t1 = 32 <=> 0
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"  // 0x80000000
);

SIM_TEST(Instr, sllv_27,
    R"(
      .text
        lui $t0, 32768     # $t0 = 0x80000000
        ori $t1, $zero, 1  # $t1 = 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_28,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 33  # $t1 = 33 <=> 1
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_29,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 16  # $t1 = 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_30,
    R"(
      .text
        lui $t0, 32768       # $t0 = 0x80000000
        lui $t1, 21845
        ori $t1, $t1, 21840  # $t1 = 1431655760 <=> 16
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_31,
    R"(
      .text
        lui $t0, 32768      # $t0 = 0x80000000
        ori $t1, $zero, 31  # $t1 = 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, sllv_32,
    R"(
      .text
        lui $t0, 32768       # $t0 = 0x80000000
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1 <=> 31
        sllv $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

// clang-format on
