#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, addiu_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        addiu $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, addiu_2,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        addiu $a0, $t0, -2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, addiu_3,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        addiu $a0, $t0, 65534
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);


SIM_TEST(Instr, addiu_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        addiu $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, addiu_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        addiu $a0, $t0, -2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-3"
);

SIM_TEST(Instr, addiu_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        addiu $a0, $t0, 65534
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-3"
);

SIM_TEST(Instr, addiu_7,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 32768  # $t0 = 2147450880
        addiu $a0, $t0, 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, addiu_8,
    R"(
      .text
        lui $t0,32768
        ori $t0, $t0, 32768  # $t0 = -2147450880
        addiu $a0, $t0, -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, addiu_9,
    R"(
      .text
        lui $t0,32768
        ori $t0, $t0, 32768  # $t0 = -2147450880
        addiu $a0, $t0, 32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, addiu_10,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addiu $a0, $t0, -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483646"
);

SIM_TEST(Instr, addiu_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addiu $a0, $t0, 65535
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483646"
);

SIM_TEST(Instr, addiu_12,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        addiu $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483647"
);

SIM_TEST(Instr, addiu_13,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 32769  # $t0 = 2147450881
        addiu $a0, $t0, 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, addiu_14,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 32767  # $t0 = -2147450881
        addiu $a0, $t0, -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, addiu_15,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 32767  # $t0 = -2147450881
        addiu $a0, $t0, 32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, addiu_16,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addiu $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, addiu_17,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 65535
        addiu $a0, $t0, -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, addiu_18,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 65535
        addiu $a0, $t0, 65535
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, addiu_19,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addiu $a0, $t0, 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147450882"
);

SIM_TEST(Instr, addiu_20,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        addiu $a0, $t0, -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147450880"
);

SIM_TEST(Instr, addiu_21,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        addiu $a0, $t0, 32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147450880"
);

// clang-format on
