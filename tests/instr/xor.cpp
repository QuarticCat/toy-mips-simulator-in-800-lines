#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, xor_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        ori $t1, $zero, 6  # $t1 = 6
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "3"
);

SIM_TEST(Instr, xor_2,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 43690
        ori $t1, $t1, 43690  # $t1 = 0xAAAAAAAA
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1"  // 0xFFFFFFFF
);

SIM_TEST(Instr, xor_3,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 255
        ori $t1, $t1, 255    # $t1 = 0x00FF00FF
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1437226410"  // 0x55AA55AA
);

SIM_TEST(Instr, xor_4,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845     # $t0 = 0x55555555
        addu $t1, $zero, $zero  # $t1 = 0x00000000
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431655765"  // 0x55555555
);

SIM_TEST(Instr, xor_5,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 0xFFFFFFFF
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431655766"  // 0xAAAAAAAA
);

SIM_TEST(Instr, xor_6,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        lui $t1, 255
        ori $t1, $t1, 255    # $t1 = 0x00FF00FF
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1437226411"  // 0xAA55AA55
);

SIM_TEST(Instr, xor_7,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690     # $t0 = 0xAAAAAAAA
        addu $t1, $zero, $zero  # $t1 = 0x00000000
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431655766"  // 0xAAAAAAAA
);

SIM_TEST(Instr, xor_8,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 0xFFFFFFFF
        xor $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431655765"  // 0x55555555
);

// clang-format on
