#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, andi_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        andi $a0, $t0, 6
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "4"
);

SIM_TEST(Instr, andi_2,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845   # $t0 = 0x55555555
        andi $a0, $t0, 43690        # 0x0000AAAA
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, andi_3,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        andi $a0, $t0, 255         # 0x000000FF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "85"  // 0x00000055
);

SIM_TEST(Instr, andi_4,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        andi $a0, $t0, 0           # 0x00000000
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, andi_5,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        andi $a0, $t0, 65535       # 0x0000FFFF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "21845"  // 0x00005555
);

SIM_TEST(Instr, andi_6,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        andi $a0, $t0, 255         # 0x000000FF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "170"  // 0x000000AA
);

SIM_TEST(Instr, andi_7,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        andi $a0, $t0, 0           # 0x00000000
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "0"  // 0x00000000
);

SIM_TEST(Instr, andi_8,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        andi $a0, $t0, 65535       # 0x0000FFFF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "43690"  // 0x0000AAAA
);

// clang-format on
