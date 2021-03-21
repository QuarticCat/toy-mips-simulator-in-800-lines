#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, add_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, add_2,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        addu $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, add_3,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        ori $t1, $zero, 2    # $t1 = 2
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, add_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 65535
        ori $t1, $t1, 65534  # $t1 = -2
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-3"
);

SIM_TEST(Instr, add_5,
    R"(
      .text
        lui $t0, 16384       # $t0 = 1073741824
        lui $t1, 16383
        ori $t1, $t1, 65535  # $t1 = 1073741823
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, add_6,
    R"(
      .text
        lui $t0, 49152  # $t0 = -1073741824
        lui $t1, 49152  # $t1 = -1073741824
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, add_7,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483646"
);

SIM_TEST(Instr, add_8,
    R"(
      .text
        lui $t0, 32768     # $t0 = -2147483648
        ori $t1, $zero, 1  # $t1 = 1
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483647"
);

SIM_TEST(Instr, add_9,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        add $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TRAP_TEST(Instr, add_10,
    R"(
      .text
        lui $t0, 16384
        ori $t0, $t0, 1      # $t0 = 1073741825
        lui $t1, 16383
        ori $t1, $t1, 65535  # $t1 = 1073741823
        add $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, add_11,
    R"(
      .text
        lui $t0, 49151
        ori $t0, $t0, 65535  # $t0 = -1073741825
        lui $t1, 49152       # $t1 = -1073741824
        add $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, add_12,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 1    # $t1 = 1
        add $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, add_13,
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        add $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, add_14,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $t0, $zero  # $t1 = 2147483647
        add $t2, $t0, $t1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, add_15,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        add $t2, $t0, $t1
    )",
    "",
    ""
);

// clang-format on
