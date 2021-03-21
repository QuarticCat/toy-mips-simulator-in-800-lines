#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, div_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        ori $t1, $zero, 2  # $t1 = 2
        div $t0, $t1
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
    "1 2"
);

SIM_TEST(Instr, div_2,
    R"(
      .text
        ori $t0, $zero, 5    # $t0 = 5
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        div $t0, $t1
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
    "1 -2"
);

SIM_TEST(Instr, div_3,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65531  # $t0 = -5
        ori $t1, $t1, 2      # $t1 = 2
        div $t0, $t1
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
    "-1 -2"
);

SIM_TEST(Instr, div_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65531  # $t0 = -5
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        div $t0, $t1
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
    "-1 2"
);

SIM_TEST(Instr, div_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        ori $t1, $zero, 2    # $t1 = 2
        div $t0, $t1
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
    "-1 0"
);

SIM_TEST(Instr, div_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        div $t0, $t1
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
    "-1 0"
);

SIM_TEST(Instr, div_7,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        div $t0, $t1
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
    "1 1073741823"
);

SIM_TEST(Instr, div_8,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        div $t0, $t1
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
    "1 -1073741823"
);

SIM_TEST(Instr, div_9,
    R"(
      .text
        lui $t0, 32768     # $t0 = -2147483648
        ori $t1, $zero, 2  # $t1 = 2
        div $t0, $t1
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
    "0 -1073741824"
);


SIM_TEST(Instr, div_10,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        div $t0, $t1
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
    "0 1073741824"
);

SIM_TEST(Instr, div_11,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        div $t0, $t1
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
    "-1 0"
);

SIM_TEST(Instr, div_12,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 32768       # $t1 = -2147483648
        div $t0, $t1
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
    "-1 0"
);

SIM_TEST(Instr, div_13,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        div $t0, $t1
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
    "0 -2147483647"
);

SIM_TEST(Instr, div_14,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = -2147483648
        div $t0, $t1
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
    "2147483647 0"
);

SIM_TEST(Instr, div_15,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 1      # $t0 = -2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        div $t0, $t1
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
    "0 2147483647"
);

SIM_TEST(Instr, div_16,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        div $t0, $t1
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
    "-1 -1"
);

// clang-format on
