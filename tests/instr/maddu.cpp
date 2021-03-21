#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, maddu_1,
    R"(
      .text
        mthi $zero
        mtlo $zero         # hi lo = 0 0
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_2,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_3,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        ori $t1, $zero, 2    # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_4,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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
    "-3 2" // 4294967293 2
);

SIM_TEST(Instr, maddu_5,
    R"(
      .text
        mthi $zero
        mtlo $zero  # hi lo = 0 0
        lui $t0, 1  # $t0 = 65536
        lui $t1, 1  # $t1 = 65536
        maddu $t0, $t1
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
    "1 0" // 1 0
);

SIM_TEST(Instr, maddu_6,
    R"(
      .text
        mthi $zero
        mtlo $zero             # hi lo = 0 0
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_7,
    R"(
      .text
        mthi $zero
        mtlo $zero      # hi lo = 0 0
        lui $t0, 65535  # $t0 = 4294901760
        lui $t1, 65535  # $t1 = 4294901760
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_8,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = 4294967295
        addu $t1, $t0, $zero  # $t1 = 4294967295
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_9,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_10,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_11,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_12,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_13,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = 2147483648
        ori $t1, $zero, 2    # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_14,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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


SIM_TEST(Instr, maddu_15,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $zero, $t0  # $t1 = 2147483647
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_16,
    R"(
      .text
        mthi $zero
        mtlo $zero      # hi lo = 0 0
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_17,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_18,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0           # hi lo = 0 3
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_19,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0             # hi lo = 0 3
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_20,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0               # hi lo = 0 3
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_21,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0        # hi lo = 0 3
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_22,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0              # hi lo = 0 3
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        maddu $t0, $t1
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
    "32767 -2147483645"  // 32767 2147483651
);

SIM_TEST(Instr, maddu_23,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0           # hi lo = 0 4294967295
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_24,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0             # hi lo = 0 4294967295
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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
    "1 -3"  // 1 4294967293
);

SIM_TEST(Instr, maddu_25,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0               # hi lo = 0 4294967295
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_26,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0        # hi lo = 0 4294967295
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_27,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0              # hi lo = 0 4294967295
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        maddu $t0, $t1
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
    "-2147483648 2147483647"  // 2147483648 2147483647
);

SIM_TEST(Instr, maddu_28,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0           # hi lo = 4294967295 4294967295
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_29,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0             # hi lo = 4294967295 4294967295
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_30,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0               # hi lo = 4294967295 4294967295
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_31,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0        # hi lo = 4294967295 4294967295
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        maddu $t0, $t1
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

SIM_TEST(Instr, maddu_32,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0              # hi lo = 4294967295 4294967295
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        maddu $t0, $t1
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
    "2147483647 2147483647"  // 2147483647 2147483647
);

// clang-format on
