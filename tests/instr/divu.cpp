#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, divu_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        ori $t1, $zero, 2  # $t1 = 2
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 2"  // 1 2
);

SIM_TEST(Instr, divu_2,
    R"(
      .text
        ori $t0, $zero, 5    # $t0 = 5
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "5 0"  // 5 0
);

SIM_TEST(Instr, divu_3,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65531  # $t0 = 4294967291
        ori $t1, $t1, 2      # $t1 = 2
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 2147483645"  // 1 2147483645
);

SIM_TEST(Instr, divu_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65531  # $t0 = 4294967291
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-5 0"  // 4294967291 0
);

SIM_TEST(Instr, divu_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        ori $t1, $zero, 2    # $t1 = 2
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 2147483647"  // 1 2147483647
);

SIM_TEST(Instr, divu_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 1"  // 1 1
);

SIM_TEST(Instr, divu_7,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 1073741823"  // 1 1073741823
);

SIM_TEST(Instr, divu_8,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647 0"  // 2147483647 0
);

SIM_TEST(Instr, divu_9,
    R"(
      .text
        lui $t0, 32768     # $t0 = 2147483648
        ori $t1, $zero, 2  # $t1 = 2
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0 1073741824"  // 0 1073741824
);


SIM_TEST(Instr, divu_10,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648 0"  // 2147483648 0
);

SIM_TEST(Instr, divu_11,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 2"  // 1 2
);

SIM_TEST(Instr, divu_12,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 32768       # $t1 = 2147483648
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647 1"  // 2147483647 1
);

SIM_TEST(Instr, divu_13,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647 0"  // 2147483647 0
);

SIM_TEST(Instr, divu_14,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = 2147483648
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647 0"  // 2147483647 0
);

SIM_TEST(Instr, divu_15,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 1      # $t0 = 2147483649
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483647 0"  // 2147483649 0
);

SIM_TEST(Instr, divu_16,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1 1"  // 1 1
);

SIM_TEST(Instr, divu_17,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        divu $t0, $t1
        mfhi $a0
        ori $v0, $zero, 1
        syscall
        ori $a0, $zero, 32
        ori $v0, $zero, 11
        syscall
        mflo $a0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648 0"  // 2147483648 0
);

// clang-format on
