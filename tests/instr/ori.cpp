#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, ori_1,
    R"(
      .text
        ori $t0, $zero, 5  # $t0 = 5
        ori $a0, $t0, 6
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "7"
);

SIM_TEST(Instr, ori_2,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        ori $a0, $t0, 43690        # 0x0000AAAA
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431699455"  // 0x5555FFFF
);

SIM_TEST(Instr, ori_3,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        ori $a0, $t0, 255          # 0x000000FF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431655935"  // 0x555555FF
);

SIM_TEST(Instr, ori_4,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        ori $a0, $t0, 0            # 0x00000000
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431655765"  // 0x55555555
);

SIM_TEST(Instr, ori_5,
    R"(
      .text
        lui $t0, 21845
        ori $t0, $t0, 21845  # $t0 = 0x55555555
        ori $a0, $t0, 65535        # 0x0000FFFF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1431699455"  // 0x5555FFFF
);

SIM_TEST(Instr, ori_6,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        ori $a0, $t0, 255          # 0x000000FF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431655681"  // 0xAAAAAAFF
);

SIM_TEST(Instr, ori_7,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        ori $a0, $t0, 0            # 0x00000000
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431655766"  // 0xAAAAAAAA
);

SIM_TEST(Instr, ori_8,
    R"(
      .text
        lui $t0, 43690
        ori $t0, $t0, 43690  # $t0 = 0xAAAAAAAA
        ori $a0, $t0, 65535        # 0x0000FFFF
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "-1431633921"  // 0xAAAAFFFF
);

// clang-format on
