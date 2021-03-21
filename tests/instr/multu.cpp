#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, multu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        multu $t0, $t1
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
    "0 2"  // 0 2
);

SIM_TEST(Instr, multu_2,
    R"(
      .text
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        multu $t0, $t1
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
    "0 -2"  // 0 4294967294
);

SIM_TEST(Instr, multu_3,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        ori $t1, $zero, 2    # $t1 = 2
        multu $t0, $t1
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
    "1 -2"  // 1 4294967294
);

SIM_TEST(Instr, multu_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        multu $t0, $t1
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
    "-3 2"  // 4294967293 2
);

SIM_TEST(Instr, multu_5,
    R"(
      .text
        lui $t0, 1  # $t0 = 65536
        lui $t1, 1  # $t1 = 65536
        multu $t0, $t1
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
    "1 0"  // 1 0
);

SIM_TEST(Instr, multu_6,
    R"(
      .text
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        mult $t0, $t1
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
    "0 -1" // 0 4294967295
);

SIM_TEST(Instr, multu_7,
    R"(
      .text
        lui $t0, 65535  # $t0 = 4294901760
        lui $t1, 65535  # $t1 = 4294901760
        multu $t0, $t1
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
    "-131071 0"  // 4294836225 0
);

SIM_TEST(Instr, multu_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = 4294967295
        addu $t1, $t0, $zero  # $t1 = 4294967295
        multu $t0, $t1
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
    "-2 1"  // 4294967294 1
);

SIM_TEST(Instr, multu_9,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        multu $t0, $t1
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
    "2147483646 -2147483647"  // 2147483646 2147483649
);

SIM_TEST(Instr, multu_10,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        multu $t0, $t1
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
    "2147483647 -2147483648"  // 2147483647 2147483648
);

SIM_TEST(Instr, multu_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        multu $t0, $t1
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
    "0 -2"  // 0 4294967294
);

SIM_TEST(Instr, multu_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        multu $t0, $t1
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
    "2147483646 2"  // 2147483646 2
);

SIM_TEST(Instr, multu_13,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        ori $t1, $zero, 2    # $t1 = 2
        multu $t0, $t1
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
    "1 0"  // 1 0
);

SIM_TEST(Instr, multu_14,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        multu $t0, $t1
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

SIM_TEST(Instr, multu_15,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $zero, $t0  # $t1 = 2147483647
        multu $t0, $t1
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
    "1073741823 1"  // 1073741823 1
);

SIM_TEST(Instr, multu_16,
    R"(
      .text
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        multu $t0, $t1
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
    "1073741824 0"  // 1073741824 0
);

SIM_TEST(Instr, multu_17,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        multu $t0, $t1
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
    "1073741823 -2147483648"  // 1073741823 2147483648
);

// clang-format on
