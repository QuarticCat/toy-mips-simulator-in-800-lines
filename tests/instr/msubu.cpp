#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, msubu_1,
    R"(
      .text
        mthi $zero
        mtlo $zero         # hi lo = 0 0
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        msubu $t0, $t1
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
    "-1 -2"  // 4294836225 4294836224
);

SIM_TEST(Instr, msubu_2,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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
    "-1 2"  // 4294836225 2
);

SIM_TEST(Instr, msubu_3,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        ori $t1, $zero, 2    # $t1 = 2
        msubu $t0, $t1
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
    "-2 2"  // 4294836224 2
);

SIM_TEST(Instr, msubu_4,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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
    "2 -2"  // 2 4294836224
);

SIM_TEST(Instr, msubu_5,
    R"(
      .text
        mthi $zero
        mtlo $zero  # hi lo = 0 0
        lui $t0, 1  # $t0 = 65536
        lui $t1, 1  # $t1 = 65536
        msubu $t0, $t1
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
    "-1 0"  // 4294836225 0
);

SIM_TEST(Instr, msubu_6,
    R"(
      .text
        mthi $zero
        mtlo $zero             # hi lo = 0 0
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        msubu $t0, $t1
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
    "-1 1"  // 4294836225 1
);

SIM_TEST(Instr, msubu_7,
    R"(
      .text
        mthi $zero
        mtlo $zero      # hi lo = 0 0
        lui $t0, 65535  # $t0 = 4294901760
        lui $t1, 65535  # $t1 = 4294901760
        msubu $t0, $t1
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
    "131071 0"  // 131071 0
);

SIM_TEST(Instr, msubu_8,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = 4294967295
        addu $t1, $t0, $zero  # $t1 = 4294967295
        msubu $t0, $t1
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
    "1 -1"  // 1 4294836225
);

SIM_TEST(Instr, msubu_9,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        msubu $t0, $t1
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
    "-2147483647 2147483647"  // 2147483649 2147483647
);

SIM_TEST(Instr, msubu_10,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        msubu $t0, $t1
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
    "-2147483648 -2147483648"  // 2147483648 2147483648
);

SIM_TEST(Instr, msubu_11,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        msubu $t0, $t1
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
    "-1 2"  // 4294967295 2
);

SIM_TEST(Instr, msubu_12,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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
    "-2147483647 -2"  // 2147483649 4294967294
);

SIM_TEST(Instr, msubu_13,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = 2147483648
        ori $t1, $zero, 2    # $t1 = 2
        msubu $t0, $t1
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
    "-1 0"  // 4294967295 0
);

SIM_TEST(Instr, msubu_14,
    R"(
      .text
        mthi $zero
        mtlo $zero           # hi lo = 0 0
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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


SIM_TEST(Instr, msubu_15,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $zero, $t0  # $t1 = 2147483647
        msubu $t0, $t1
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
    "-1073741824 -1"  // 3221225472 4294967295
);

SIM_TEST(Instr, msubu_16,
    R"(
      .text
        mthi $zero
        mtlo $zero      # hi lo = 0 0
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        msubu $t0, $t1
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
    "-1073741824 0"  // 3221225472 0
);

SIM_TEST(Instr, msubu_17,
    R"(
      .text
        mthi $zero
        mtlo $zero            # hi lo = 0 0
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        msubu $t0, $t1
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
    "-1073741824 -2147483648"  // 3221225472 2147483648
);

SIM_TEST(Instr, msubu_18,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0           # hi lo = 0 3
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        msubu $t0, $t1
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

SIM_TEST(Instr, msubu_19,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0             # hi lo = 0 3
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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
    "-1 5"  // 4294967295 5
);

SIM_TEST(Instr, msubu_20,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0               # hi lo = 0 3
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        msubu $t0, $t1
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
    "-1 4"  // 4294967295 4
);

SIM_TEST(Instr, msubu_21,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0        # hi lo = 0 3
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        msubu $t0, $t1
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
    "-1073741824 3"  // 3221225472 3
);

SIM_TEST(Instr, msubu_22,
    R"(
      .text
        ori $t0, $zero, 3
        mthi $zero
        mtlo $t0              # hi lo = 0 3
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        msubu $t0, $t1
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
    "-32768 -2147483645"  // 4294934528 2147483651
);

SIM_TEST(Instr, msubu_23,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0           # hi lo = 0 4294967295
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        msubu $t0, $t1
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

SIM_TEST(Instr, msubu_24,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0             # hi lo = 0 4294967295
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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

SIM_TEST(Instr, msubu_25,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0               # hi lo = 0 4294967295
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        msubu $t0, $t1
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
    "0 0"  // 0 0
);

SIM_TEST(Instr, msubu_26,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0        # hi lo = 0 4294967295
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        msubu $t0, $t1
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
    "-1073741824 -1"  // 3221225472 4294967295
);

SIM_TEST(Instr, msubu_27,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $zero
        mtlo $t0              # hi lo = 0 4294967295
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        msubu $t0, $t1
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
    "-2147483647 2147483647"  // 2147483649 2147483647
);

SIM_TEST(Instr, msubu_28,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0           # hi lo = 4294967295 4294967295
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        msubu $t0, $t1
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
    "-1 -3"  // 4294967295 4294967293
);

SIM_TEST(Instr, msubu_29,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0             # hi lo = 4294967295 4294967295
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = 4294967294
        msubu $t0, $t1
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
    "-1 1"  // 4294967295 1
);

SIM_TEST(Instr, msubu_30,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0               # hi lo = 4294967295 4294967295
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        msubu $t0, $t1
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
    "-1 0"  // 4294967295 0
);

SIM_TEST(Instr, msubu_31,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0        # hi lo = 4294967295 4294967295
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        msubu $t0, $t1
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
    "-1073741825 -1"  // 3221225471 4294967295
);

SIM_TEST(Instr, msubu_32,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535
        mthi $t0
        mtlo $t0              # hi lo = 4294967295 4294967295
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = 2147483648
        msubu $t0, $t1
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

// clang-format on
