#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, mul_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, mul_2,
    R"(
      .text
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"
);

SIM_TEST(Instr, mul_3,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        ori $t1, $zero, 2    # $t1 = 2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"
);

SIM_TEST(Instr, mul_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, mul_5,
    R"(
      .text
        lui $t0, 1  # $t0 = 65536
        lui $t1, 1  # $t1 = 65536
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, mul_6,
    R"(
      .text
        ori $t0, $zero, 65535  # $t0 = 65535
        lui $t1, 1
        ori $t1, $t1, 1        # $t1 = 65537
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, mul_7,
    R"(
      .text
        lui $t0, 65535  # $t0 = -65536
        lui $t1, 65535  # $t1 = -65536
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, mul_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = -1
        addu $t1, $t0, $zero  # $t1 = -1
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, mul_9,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483647"
);

SIM_TEST(Instr, mul_10,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, mul_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 2    # $t1 = 2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2"
);

SIM_TEST(Instr, mul_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2"
);

SIM_TEST(Instr, mul_13,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        ori $t1, $zero, 2    # $t1 = 2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, mul_14,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);


SIM_TEST(Instr, mul_15,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $zero, $t0  # $t1 = 2147483647
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, mul_16,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, mul_17,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        lui $t1, 32768        # $t1 = -2147483648
        mul $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

// clang-format on
