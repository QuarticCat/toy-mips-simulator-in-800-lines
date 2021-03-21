#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, tgei_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgei $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgei_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tgei $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tgei $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        tgei $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        tgei $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tgei $t0, -1         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tgei $t0, 65535      # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_8,
    R"(
      .text
        ori $t0, $zero, 0  # $t0 = 0
        tgei $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_9,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgei $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_10,
    R"(
      .text
        ori $t0, $zero, 32767  # $t0 = 32767
        tgei $t0, 32767        # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgei_11,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        tgei $t0, -1    # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tgei_12,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        tgei $t0, 65535  # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgei_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tgei $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tgei $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgei_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tgei $t0, 0          # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgei_16,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tgei $t0, -1            # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_17,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tgei $t0, 65535         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgei_18,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tgei $t0, 1             # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgei_19,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgei $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgei_20,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tgei $t0, 32767    # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tgei_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tgei $t0, 1          # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tgei $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tgei_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tgei $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tgei_24,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        tgei $t0, 32767  # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
