#include "test_util.hpp"

// clang-format off

SIM_TRAP_TEST(Instr, tlti_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tlti $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlti_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tlti $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        tlti $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        tlti $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        tlti $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tlti $t0, -1         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tlti $t0, 65535      # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_8,
    R"(
      .text
        ori $t0, $zero, 0  # $t0 = 0
        tlti $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_9,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tlti $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_10,
    R"(
      .text
        ori $t0, $zero, 32767  # $t0 = 32767
        tlti $t0, 32767        # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlti_11,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        tlti $t0, -1    # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, tlti_12,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        tlti $t0, 65535  # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlti_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tlti $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tlti $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlti_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        tlti $t0, 0          # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlti_16,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tlti $t0, -1            # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_17,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tlti $t0, 65535         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlti_18,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        tlti $t0, 1             # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlti_19,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tlti $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlti_20,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        tlti $t0, 32767    # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, tlti_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tlti $t0, 1          # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tlti $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, tlti_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        tlti $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, tlti_24,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        tlti $t0, 32767  # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

// clang-format on
