#include "test_util.hpp"

// clang-format off

SIM_TRAP_TEST(Instr, tlt_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlt_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 1  # $t1 = 1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 2  # $t1 = 2
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_4,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = -1
        addu $t1, $t0, $zero  # $t1 = -1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_6,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        addu $t1, $zero, $zero  # $t1 = 0
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_7,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 1  # $t1 = 1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_8,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $t0, $zero  # $t1 = 2147483647
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlt_9,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlt_10,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 32768       # $t1 = -2147483648
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlt_11,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535     # $t0 = -1
        addu $t1, $zero, $zero  # $t1 = 0
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlt_12,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        lui $t1, 65535
        ori $t1, $t1, 65535     # $t1 = -1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlt_13,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        ori $t1, $zero, 1       # $t1 = 1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlt_14,
    R"(
      .text
        ori $t0, $zero, 1       # $t0 = 1
        addu $t1, $zero, $zero  # $t1 = 0
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlt_15,
    R"(
      .text
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlt_16,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 1    # $t1 = 1
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlt_17,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = -2147483648
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlt_18,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        tlt $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

// clang-format on
