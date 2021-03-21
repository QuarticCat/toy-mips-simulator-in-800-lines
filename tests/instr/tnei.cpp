#include "test_util.hpp"

// clang-format off

SIM_TRAP_TEST(Instr, tnei_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tnei $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tnei $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tnei_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tnei $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        tnei $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        tnei $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tnei $t0, -1         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tnei $t0, 65535      # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_8,
    R"(
      .text
        ori $t0, $zero, 0  # $t0 = 0
        tnei $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_9,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tnei $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tnei_10,
    R"(
      .text
        ori $t0, $zero, 32767  # $t0 = 32767
        tnei $t0, 32767        # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tnei_11,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        tnei $t0, -1    # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_12,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        tnei $t0, 65535  # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tnei $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tnei $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tnei $t0, 0          # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_16,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tnei $t0, -1            # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_17,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tnei $t0, 65535         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_18,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tnei $t0, 1             # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_19,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tnei $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_20,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tnei $t0, 32767    # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tnei $t0, 1          # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tnei $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tnei $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tnei_24,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        tnei $t0, 32767  # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

// clang-format on
