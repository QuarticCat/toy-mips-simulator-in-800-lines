#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, teqi_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        teqi $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        teqi $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, teqi_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        teqi $t0, 2        # 2
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        teqi $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 32768  # $t0 = -32768
        teqi $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        teqi $t0, -1         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        teqi $t0, 65535      # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_8,
    R"(
      .text
        ori $t0, $zero, 0  # $t0 = 0
        teqi $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_9,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        teqi $t0, 1        # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teqi_10,
    R"(
      .text
        ori $t0, $zero, 32767  # $t0 = 32767
        teqi $t0, 32767        # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, teqi_11,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        teqi $t0, -1    # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_12,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        teqi $t0, 65535  # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_13,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        teqi $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_14,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        teqi $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_15,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        teqi $t0, 0          # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_16,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        teqi $t0, -1            # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_17,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        teqi $t0, 65535         # -1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_18,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        teqi $t0, 1             # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_19,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        teqi $t0, 0        # 0
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_20,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        teqi $t0, 32767    # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_21,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        teqi $t0, 1          # 1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_22,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        teqi $t0, -32768     # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_23,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        teqi $t0, 32768      # -32768
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teqi_24,
    R"(
      .text
        lui $t0, 32768   # $t0 = -2147483648
        teqi $t0, 32767  # 32767
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
