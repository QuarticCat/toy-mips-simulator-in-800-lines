#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, tgeiu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgeiu $t0, 2       # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeiu_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tgeiu $t0, 1       # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tgeiu $t0, 2       # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = 4294934528
        tgeiu $t0, -32768    # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = 4294934528
        tgeiu $t0, 32768     # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tgeiu $t0, -1        # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tgeiu $t0, 65535     # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_8,
    R"(
      .text
        ori $t0, $zero, 0  # $t0 = 0
        tgeiu $t0, 0       # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_9,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgeiu $t0, 1       # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_10,
    R"(
      .text
        ori $t0, $zero, 32767  # $t0 = 32767
        tgeiu $t0, 32767       # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeiu_11,
    R"(
      .text
        lui $t0, 32768  # $t0 = 2147483648
        tgeiu $t0, -1   # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tgeiu_12,
    R"(
      .text
        lui $t0, 32768    # $t0 = 2147483648
        tgeiu $t0, 65535  # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeiu_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tgeiu $t0, -32768    # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tgeiu $t0, 32768     # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeiu_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tgeiu $t0, 0         # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeiu_16,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tgeiu $t0, -1           # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tgeiu_17,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tgeiu $t0, 65535        # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tgeiu_18,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tgeiu $t0, 1            # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeiu_19,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgeiu $t0, 0       # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeiu_20,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgeiu $t0, 32767   # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeiu_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tgeiu $t0, 1         # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeiu_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tgeiu $t0, -32768    # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tgeiu_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tgeiu $t0, 32768     # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeiu_24,
    R"(
      .text
        lui $t0, 32768    # $t0 = 2147483648
        tgeiu $t0, 32767  # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

// clang-format on
