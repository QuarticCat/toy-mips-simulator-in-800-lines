#include "test_util.hpp"

// clang-format off

SIM_TEST(Instr, teq_1, // NOLINT(cert-err58-cpp)
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 2  # $t1 = 2
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_2, // NOLINT(cert-err58-cpp)
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 1  # $t1 = 1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TRAP_TEST(Instr, teq_3, // NOLINT(cert-err58-cpp)
    R"(
      .text
        ori $t0, $zero, 2  # $t0 = 2
        ori $t1, $zero, 2  # $t1 = 2
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teq_4, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 32768  # $t0 = -2147483648
        lui $t1, 32768  # $t1 = -2147483648
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teq_5, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535   # $t0 = -1
        addu $t1, $t0, $zero  # $t1 = -1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teq_6, // NOLINT(cert-err58-cpp)
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        addu $t1, $zero, $zero  # $t1 = 0
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teq_7, // NOLINT(cert-err58-cpp)
    R"(
      .text
        ori $t0, $zero, 1  # $t0 = 1
        ori $t1, $zero, 1  # $t1 = 1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TRAP_TEST(Instr, teq_8, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535   # $t0 = 2147483647
        addu $t1, $t0, $zero  # $t1 = 2147483647
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    ""
);

SIM_TEST(Instr, teq_9, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 65535
        ori $t1, $t1, 65535  # $t1 = -1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_10, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535  # $t0 = -1
        lui $t1, 32768       # $t1 = -2147483648
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_11, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 65535
        ori $t0, $t0, 65535     # $t0 = -1
        addu $t1, $zero, $zero  # $t1 = 0
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_12, // NOLINT(cert-err58-cpp)
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        lui $t1, 65535
        ori $t1, $t1, 65535     # $t1 = -1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_13, // NOLINT(cert-err58-cpp)
    R"(
      .text
        addu $t0, $zero, $zero  # $t0 = 0
        ori $t1, $zero, 1       # $t1 = 1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_14, // NOLINT(cert-err58-cpp)
    R"(
      .text
        ori $t0, $zero, 1       # $t0 = 1
        addu $t1, $zero, $zero  # $t1 = 0
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_15, // NOLINT(cert-err58-cpp)
    R"(
      .text
        ori $t0, $zero, 1    # $t0 = 1
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_16, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        ori $t1, $zero, 1    # $t1 = 1
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_17, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 32767
        ori $t0, $t0, 65535  # $t0 = 2147483647
        lui $t1, 32768       # $t1 = -2147483648
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

SIM_TEST(Instr, teq_18, // NOLINT(cert-err58-cpp)
    R"(
      .text
        lui $t0, 32768       # $t0 = -2147483648
        lui $t1, 32767
        ori $t1, $t1, 65535  # $t1 = 2147483647
        teq $t0, $t1
        ori $a0, $zero, 1
        ori $v0, $zero, 1
        syscall
    )",
    "",
    "1"
);

// clang-format on
