#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, sltiu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        sltiu $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_2,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        sltiu $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_3,
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        sltiu $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_4,
    R"(
      .text
        lui $t0, 32768  # $t0 = 2147483648
        sltiu $a0, $t0, -1    # 4294967295
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_5,
    R"(
      .text
        lui $t0, 32768   # $t0 = 2147483648
        sltiu $a0, $t0, 65535  # 4294967295
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = 4294967295
        sltiu $a0, $t0, -32768      # 4294934528
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_7,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        sltiu $a0, $t0, 32768      # 4294934528
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_8,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = 4294967295
        sltiu $a0, $t0, 0          # 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_9,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        sltiu $a0, $t0, -1            # 4294967295
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_10,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        sltiu $a0, $t0, 65535         # 4294967295
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_11,
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        sltiu $a0, $t0, 1             # 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_12,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        sltiu $a0, $t0, 0        # 0
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_13,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        sltiu $a0, $t0, 32767    # 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_14,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        sltiu $a0, $t0, 1          # 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

SIM_TEST(Instr, sltiu_15,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        sltiu $a0, $t0, -32768     # 4294934528
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_16,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        sltiu $a0, $t0, 32768      # 4294934528
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, sltiu_17,
    R"(
      .text
        lui $t0, 32768   # $t0 = 2147483648
        sltiu $a0, $t0, 32767  # 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"
);

// clang-format on
