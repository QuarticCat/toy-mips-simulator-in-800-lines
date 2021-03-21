#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, madd_1,
    R"(
      .text
        mthi $zero
        mtlo $zero         # hi lo = 0 0
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        madd $t0, $t1
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

SIM_TEST(Instr, madd_2,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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
    "-1 -2"  // -1 4294967294
);

SIM_TEST(Instr, madd_3,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        ori $t1, $zero, 2    # $t1 = 2
        madd $t0, $t1
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
    "-1 -2"  // -1 4294967294
);

SIM_TEST(Instr, madd_4,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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

SIM_TEST(Instr, madd_5,
    R"(
      .text
        mthi $zero
        mtlo $zero  # hi lo = 0 0
        lui $t0, 1  # $t0 = 65536
        lui $t1, 1  # $t1 = 65536
        madd $t0, $t1
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

SIM_TEST(Instr, madd_6,
    R"(
      .text
        mthi $zero
        mtlo $zero             # hi lo = 0 0
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        madd $t0, $t1
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
    "0 -1"  // 0 4294967295
);

SIM_TEST(Instr, madd_7,
    R"(
      .text
        mthi $zero
        mtlo $zero      # hi lo = 0 0
        lui $t0, 65535  # $t0 = -65536
        lui $t1, 65535  # $t1 = -65536
        madd $t0, $t1
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

SIM_TEST(Instr, madd_8,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = -1
        addu $t1, $t0, $zero  # $t1 = -1
        madd $t0, $t1
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
    "0 1"  // 0 1
);

SIM_TEST(Instr, madd_9,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        madd $t0, $t1
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
    "-1 -2147483647"  // -1 2147483649
);

SIM_TEST(Instr, madd_10,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        madd $t0, $t1
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
    "0 -2147483648"  // 0 2147483648
);

SIM_TEST(Instr, madd_11,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        madd $t0, $t1
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

SIM_TEST(Instr, madd_12,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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
    "-1 2"  // -1 2
);

SIM_TEST(Instr, madd_13,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = -2147483648
        ori $t1, $zero, 2    # $t1 = 2
        madd $t0, $t1
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
    "-1 0"  // -1 0
);

SIM_TEST(Instr, madd_14,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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


SIM_TEST(Instr, madd_15,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $zero, $t0  # $t1 = 2147483647
        madd $t0, $t1
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

SIM_TEST(Instr, madd_16,
    R"(
      .text
        mthi $zero
        mtlo $zero      # hi lo = 0 0
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        madd $t0, $t1
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

SIM_TEST(Instr, madd_17,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = -2147483648
        madd $t0, $t1
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
    "-1073741824 -2147483648"  // -1073741824 2147483648
);

SIM_TEST(Instr, madd_18,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0           # hi lo = 0 3
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        madd $t0, $t1
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
    "0 5"  // 0 5
);

SIM_TEST(Instr, madd_19,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0             # hi lo = 0 3
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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
    "0 1"  // 0 1
);

SIM_TEST(Instr, madd_20,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0               # hi lo = 0 3
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        madd $t0, $t1
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

SIM_TEST(Instr, madd_21,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0        # hi lo = 0 3
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        madd $t0, $t1
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
    "1073741824 3"  // 1073741824 3
);

SIM_TEST(Instr, madd_22,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0              # hi lo = 0 3
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = -2147483648
        madd $t0, $t1
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
    "-32768 -2147483645"  // -32768 2147483651
);

SIM_TEST(Instr, madd_23,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0           # hi lo = 0 4294967295
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        madd $t0, $t1
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

SIM_TEST(Instr, madd_24,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0             # hi lo = 0 4294967295
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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
    "0 -3"  // 0 4294967293
);

SIM_TEST(Instr, madd_25,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0               # hi lo = 0 4294967295
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        madd $t0, $t1
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

SIM_TEST(Instr, madd_26,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0        # hi lo = 0 4294967295
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        madd $t0, $t1
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
    "1073741824 -1"  // 1073741824 4294967295
);

SIM_TEST(Instr, madd_27,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0              # hi lo = 0 4294967295
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = -2147483648
        madd $t0, $t1
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

SIM_TEST(Instr, madd_28,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0           # hi lo = -1 4294967295
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        madd $t0, $t1
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
    "0 1"  // 0 1
);

SIM_TEST(Instr, madd_29,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0             # hi lo = -1 4294967295
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        madd $t0, $t1
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
    "-1 -3"  // -1 4294967293
);

SIM_TEST(Instr, madd_30,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0               # hi lo = -1 4294967295
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        madd $t0, $t1
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

SIM_TEST(Instr, madd_31,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0        # hi lo = -1 4294967295
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        madd $t0, $t1
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
    "1073741823 -1"  // 1073741823 4294967295
);

SIM_TEST(Instr, madd_32,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0              # hi lo = -1 4294967295
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = -2147483648
        madd $t0, $t1
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
    "0 2147483647"  // 0 2147483647
);

// clang-format on
