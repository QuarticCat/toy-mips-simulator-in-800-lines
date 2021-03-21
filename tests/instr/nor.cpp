#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, nor_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        ori $t1, $zero, 6  # $t1 = 6
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-8"
);

SIM_TEST(Instr, nor_2,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 43690
        ori $t1, $t1, 43690  # $t1 = 0xAAAAAAAA
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, nor_3,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 255
        ori $t1, $t1, 255    # $t1 = 0x00FF00FF
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1442797056"  // 0xAA00AA00
);

SIM_TEST(Instr, nor_4,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845     # $t0 = 0x55555555
        addu $t1, $zero, $zero  # $t1 = 0x00000000
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431655766"  // 0xAAAAAAAA
);

SIM_TEST(Instr, nor_5,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 0xFFFFFFFF
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, nor_6,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        lui $t1, 255
        ori $t1, $t1, 255    # $t1 = 0x00FF00FF
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1426085120"  // 0x55005500
);

SIM_TEST(Instr, nor_7,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690     # $t0 = 0xAAAAAAAA
        addu $t1, $zero, $zero  # $t1 = 0x00000000
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431655765"  // 0x55555555
);

SIM_TEST(Instr, nor_8,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 0xFFFFFFFF
        nor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

// clang-format on
