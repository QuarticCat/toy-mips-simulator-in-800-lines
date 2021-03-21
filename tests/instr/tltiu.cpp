#include "test_util.hpp"

// clang-format off

SIM_TRAP_TEST(Instr, tltiu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tltiu $t0, 2       # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tltiu_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tltiu $t0, 1       # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tltiu $t0, 2       # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = 4294934528
        tltiu $t0, -32768    # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = 4294934528
        tltiu $t0, 32768     # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tltiu $t0, -1        # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tltiu $t0, 65535     # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_8,
    R"(
      .text
        ori $t0, $zero, 0  # $t0 = 0
        tltiu $t0, 0       # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_9,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tltiu $t0, 1       # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_10,
    R"(
      .text
        ori $t0, $zero, 32767  # $t0 = 32767
        tltiu $t0, 32767       # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tltiu_11,
    R"(
      .text
        lui $t0, 32768  # $t0 = 2147483648
        tltiu $t0, -1   # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tltiu_12,
    R"(
      .text
        lui $t0, 32768    # $t0 = 2147483648
        tltiu $t0, 65535  # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tltiu_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tltiu $t0, -32768    # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tltiu $t0, 32768     # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tltiu_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        tltiu $t0, 0         # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tltiu_16,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tltiu $t0, -1           # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tltiu_17,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tltiu $t0, 65535        # 4294967295
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tltiu_18,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tltiu $t0, 1            # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tltiu_19,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tltiu $t0, 0       # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tltiu_20,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tltiu $t0, 32767   # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tltiu_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tltiu $t0, 1         # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tltiu_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tltiu $t0, -32768    # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tltiu_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tltiu $t0, 32768     # 4294934528
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tltiu_24,
    R"(
      .text
        lui $t0, 32768    # $t0 = 2147483648
        tltiu $t0, 32767  # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
