#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, and_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        ori $t1, $zero, 6  # $t1 = 6
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4"
);

SIM_TEST(Instr, and_2,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 43690
        ori $t1, $t1, 43690  # $t1 = 0xAAAAAAAA
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, and_3,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 255
        ori $t1, $t1, 255    # $t1 = 0x00FF00FF
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "5570645"  // 0x00550055
);

SIM_TEST(Instr, and_4,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845     # $t0 = 0x55555555
        addu $t1, $zero, $zero  # $t1 = 0x00000000
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, and_5,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 0xFFFFFFFF
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431655765"  // 0x55555555
);

SIM_TEST(Instr, and_6,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        lui $t1, 255
        ori $t1, $t1, 255    # $t1 = 0x00FF00FF
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "11141290"  // 0x00AA00AA
);

SIM_TEST(Instr, and_7,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690     # $t0 = 0xAAAAAAAA
        addu $t1, $zero, $zero  # $t1 = 0x00000000
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, and_8,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = 0xFFFFFFFF
        and $a0, $t0, $t1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431655766"  // 0xAAAAAAAA
);

// clang-format on
