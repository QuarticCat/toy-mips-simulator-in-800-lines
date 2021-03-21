#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, addi_1,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        addi $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, addi_2,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        addi $a0, $t0, -2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, addi_3,
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        addi $a0, $t0, 65534
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"
);

SIM_TEST(Instr, addi_4,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        addi $a0, $t0, 2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, addi_5,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        addi $a0, $t0, -2
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-3"
);

SIM_TEST(Instr, addi_6,
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        addi $a0, $t0, 65534
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-3"
);

SIM_TEST(Instr, addi_7,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 32768  # $t0 = 2147450880
        addi $a0, $t0, 32767
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483647"
);

SIM_TEST(Instr, addi_8,
    R"(
      .text
        lui $t0,32768
        ori $t0, $t0, 32768  # $t0 = -2147450880
        addi $a0, $t0, -32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, addi_9,
    R"(
      .text
        lui $t0,32768
        ori $t0, $t0, 32768  # $t0 = -2147450880
        addi $a0, $t0, 32768
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483648"
);

SIM_TEST(Instr, addi_10,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addi $a0, $t0, -1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483646"
);

SIM_TEST(Instr, addi_11,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addi $a0, $t0, 65535
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "2147483646"
);

SIM_TEST(Instr, addi_12,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        addi $a0, $t0, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-2147483647"
);

SIM_TRAP_TEST(Instr, addi_13,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 32769  # $t0 = 2147450881
        addi $t1, $t0, 32767
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_14,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 32767  # $t0 = -2147450881
        addi $t1, $t0, -32768
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_15,
    R"(
      .text
        lui $t0, 32768
        ori $t0, $t0, 32767  # $t0 = -2147450881
        addi $t1, $t0, 32768
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_16,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addi $t1, $t0, 1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_17,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 65535
        addi $t1, $t0, -1
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_18,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 65535
        addi $t1, $t0, 65535
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_19,
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        addi $t1, $t0, 32767
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_20,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        addi $t1, $t0, -32768
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, addi_21,
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        addi $t1, $t0, 32768
    )",
    "",
    ""
);

// clang-format on
