#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, sub_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, sub_2,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, sub_3,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        ori $t1, $zero, 2    # $t1 = 2
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-3"
);

SIM_TEST(Instr, sub_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sub_5,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $t0, $zero  # $t0 = 2147483647
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sub_6,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sub_7,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 1    # $t1 = 1
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483646"
);

SIM_TEST(Instr, sub_8,
    R"(
      .text
        lui $t0, 32768     # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t0 = -1
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483647"
);

SIM_TEST(Instr, sub_9,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        lui $t1, 32768
        ori $t1, $t1, 1  # $t1 = -2147483647
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, sub_10,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32767
        ori $t1, $t1, 65534  # $t0 = 2147483646
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sub_11,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 1  # $t0 = -2147483647
        lui $t1, 32768   # $t1 = -2147483648
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sub_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65534  # $t0 = 2147483646
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        sub $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TRAP_TEST(Instr, sub_13,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t0 = -1
        sub $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, sub_14,
    R"(
      .text
        lui $t0, 32768     # $t0 = -2147483648
        ori $t1, $zero, 1  # $t1 = 1
        sub $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, sub_15,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = -2147483648
        sub $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, sub_16,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        sub $t2, $t0, $t1
    )",
    "",
    ""
);

// clang-format on
