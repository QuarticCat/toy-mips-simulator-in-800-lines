#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, slti_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        slti $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, slti_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        slti $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        slti $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_4,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        slti $a0, $t0, -1     # -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, slti_5,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        slti $a0, $t0, 65535  # -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, slti_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        slti $a0, $t0, -32768      # -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        slti $a0, $t0, 32768       # -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        slti $a0, $t0, 0           # 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, slti_9,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        slti $a0, $t0, -1             # -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_10,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        slti $a0, $t0, 65535          # -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_11,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        slti $a0, $t0, 1              # 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, slti_12,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        slti $a0, $t0, 0         # 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_13,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        slti $a0, $t0, 32767     # 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, slti_14,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        slti $a0, $t0, 1           # 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_15,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        slti $a0, $t0, -32768      # -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_16,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        slti $a0, $t0, 32768       # -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, slti_17,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        slti $a0, $t0, 32767  # 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
