#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, tgeu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeu_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 1  # $t1 = 1
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeu_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 2  # $t1 = 2
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);


SIM_TRAP_TEST(Instr, tgeu_4,
    R"(
      .text
        lui $t0, 32768  # $t0 = 2147483648
        lui $t1, 32768  # $t1 = 2147483648
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeu_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = 4294967295
        addu $t1, $t0, $zero  # $t1 = 4294967295
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeu_6,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        addu $t1, $zero, $zero  # $t1 = 0
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeu_7,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 1  # $t1 = 1
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeu_8,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $t0, $zero  # $t1 = 2147483647
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeu_9,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 4294967295
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeu_10,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        lui $t1, 32768       # $t1 = 2147483648
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgeu_11,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535     # $t0 = 4294967295
        addu $t1, $zero, $zero  # $t1 = 0
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeu_12,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        lui $t1, 65535
        ori $t1, $t1, 65535     # $t1 = 4294967295
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tgeu_13,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        ori $t1, $zero, 1       # $t1 = 1
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeu_14,
    R"(
      .text
        ori $t0, $zero, 1       # $t0 = 1
        addu $t1, $zero, $zero  # $t1 = 0
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeu_15,
    R"(
      .text
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeu_16,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 1    # $t1 = 1
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgeu_17,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = 2147483648
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgeu_18,
    R"(
      .text
        lui $t0, 32768       # $t0 = 2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        tgeu $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

// clang-format on
