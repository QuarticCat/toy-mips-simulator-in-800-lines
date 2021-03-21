#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

#include "test_util.hpp"

// clang-format off

SIM_TEST(SimSample, a_plus_b,
    R"(
      .text
      addi $v0, $zero, 5
      syscall
      add $t0, $zero, $v0
      addi $v0, $zero, 5
      syscall
      add $t1, $zero, $v0
      add $a0, $t1, $t0
      addi $v0, $zero, 1
      syscall
      addi $v0, $zero, 10
      syscall
    )",
    "114\n514\n",
    "628"
);

SIM_TEST(SimSample, fib,
    R"(
      .data
      # .align 2
      FIB_START: .asciiz "fib("
      # .align 2
      FIB_MID: .asciiz ") = "
      # .align 2
      LINE_END: .asciiz "\n"
      .text
      addi $v0, $zero, 5
      syscall
      add $s1, $zero, $v0

      lui $at, 80
      ori $a0, $at, 0
      addi $v0, $zero, 4
      syscall

      addu $a0, $s1, $zero
      addi $v0, $zero, 1
      syscall

      lui $at, 80
      ori $a0, $at, 8
      addi $v0, $zero, 4
      syscall

      add $a0, $zero, $s1
      jal fibonacci
      add $a0, $zero, $v0
      addi $v0, $zero, 1
      syscall

      lui $at, 80
      ori $a0, $at, 16
      addi $v0, $zero, 4
      syscall

      addi $v0, $zero, 10
      syscall

      fibonacci:
      addi $sp, $sp, -12
      sw $ra, 8($sp)
      sw $s0, 4($sp)
      sw $s1, 0($sp)
      add $s0, $a0, $zero
      addi $v0, $zero, 1
      slti $t7, $s0, 3
      bne $t7, $zero, fibonacciExit
      addi $a0, $s0, -1
      jal fibonacci
      add $s1, $zero, $v0
      addi $a0, $s0, -2
      jal fibonacci
      add $v0, $s1, $v0
      fibonacciExit:
      lw $ra, 8($sp)
      lw $s0, 4($sp)
      lw $s1, 0($sp)
      addi $sp, $sp, 12
      jr $ra
    )",
    "16\n",
    "fib(16) = 987\n"
);

// clang-format on

TEST(SimSample, memcpy_hello_world) {
    std::istringstream asm_in(R"(
      .data
      # .align 2
      HELLO: .ascii "hello, world\n"
      LENGTH: .word 13
      .text
          lui $at, 80
          ori $s0, $at, 16
          lw $s0, 0($s0)
          lui $at, 80
          ori $s3, $at, 0
          addi $v0, $zero, 9
          addi $a0, $zero, 16
          syscall
          addu $s1, $zero, $v0
          addu $a0, $zero, $v0
          addu $a1, $zero, $s3
          addu $a2, $zero, $s0
          jal __builtin_memcpy
          addi $v0, $zero, 15
          addi $a0, $zero, 1
          addu $a1, $zero, $s1
          addu $a2, $zero, $s0
          syscall
          addi $v0, $zero, 10
          syscall
      __builtin_memcpy_aligned_large:
          addi  $t7, $a2, -4
          blez  $t7, __builtin_memcpy_bytes
          lw    $t0, 0($a1)
          sw    $t0, 0($a0)
          addi  $a2, $a2, -4
          addiu $a1, $a1, 4
          addiu $a0, $a0, 4
          j     __builtin_memcpy_aligned_large
      __builtin_memcpy_bytes:
          beq   $a2, $zero, __builtin_memcpy_return
          lbu   $t0, 0($a1)
          sb    $t0, 0($a0)
          addi  $a2, $a2, -1
          addiu $a1, $a1, 1
          addiu $a0, $a0, 1
          j     __builtin_memcpy_bytes
      __builtin_memcpy_return:
          jr    $ra
      __builtin_memcpy:
          addi  $t7, $a2, -4
          blez  $t7, __builtin_memcpy_bytes
          xor   $t8, $a0, $a1
          andi  $t8, $t0, 3
          subu  $t1, $zero, $a0
          andi  $t1, $t1, 3
      __builtin_memcpy_prepare:
          beq   $t1, $zero, __builtin_memcpy_check
          lbu   $t0, 0($a1)
          sb    $t0, 0($a0)
          addi  $a2, $a2, -1
          addi  $t1, $t1, -1
          addiu $a1, $a1, 1
          addiu $a0, $a0, 1
          j     __builtin_memcpy_prepare
      __builtin_memcpy_check:
          beq   $t8, $zero, __builtin_memcpy_aligned_large
      __builtin_memcpy_unaligned_large:
          addi   $t7, $a2, -4
          blez  $t7, __builtin_memcpy_bytes
          lwl   $t0, 0($a1)
          lwr   $t0, 1($a1)
          sw    $t0, 0($a0)
          addi  $a2, $a2, -4
          addiu $a1, $a1, 4
          addiu $a0, $a0, 4
          j     __builtin_memcpy_unaligned_large
    )");
    std::istringstream in("");
    std::string ans("hello, world\n");
    testing::internal::CaptureStdout();
    auto [mem, text_end] = assemble(asm_in);
    try {
        simulate(in, std::cout, std::move(mem), text_end);
    } catch (const ExitError& e) {
        EXPECT_EQ(e.code(), 0);  // prevent folding
    }
    EXPECT_EQ(testing::internal::GetCapturedStdout(), ans);
}

TEST(SimSample, many_tests) {
    std::istringstream asm_in(R"(
      .data        #data segment starts at addr 0x00500000 (1MB for text segment)
      str1: .asciiz "Testing lb,sb,read/print_char,sbrk"            #at 0x00500000
      str2: .asciiz "Please enter a char:"                #at 0x00500024
      str3: .asciiz "The char you entered is:"            #at 0x0050003C
      str4: .asciiz "Testing for .ascii"                #at 0x00500058
      str5: .ascii "aaaa"                        #at 0x0050006C
      str6: .ascii "bbbb"                        #at 0x00500070
      str7: .asciiz "ccc"                        #at 0x00500074
      str8: .asciiz "Testing for fileIO syscalls"                #at 0x00500078
      str9: .asciiz "_tmp_file.txt"                #at 0x00500094
      str10: .asciiz "If you see this, your fileIO is all cool"    #at 0x005000A4
      str11: .asciiz "num of chars printed to file:"                #at 0x005000D0
      str12: .asciiz "Goodbye"            #at 0x005000F0
      str13: .asciiz "You should see aaaabbbbccc, bbbbccc, ccc for three strings"    #at 0x005000F8
      half: .half 1,2                        #at 0x00500134
      byte: .byte 1,2,3,4                    #at 0x00500138
      str14: .asciiz "Testing for .half,.byte"    #at 0x0050013C
      str15: .asciiz "For half, the output should be: 65539 in decimal, and you have:"    #at 0x00500154
      str16: .asciiz "For byte, the output should be: 16909059 in decimal, and you have:"    #at 0x00500194


      .text
      main:    addi $a0,$a0, 80            #load str1 addr to $a0 and print.
          sll $a0,$a0,16
          addi $v0, $zero, 4
          syscall

          lui $a0, 80                #load str2 addr to $a0 and print.
          ori $a0, $a0, 36
          addi $v0, $zero, 4
          syscall

          addi $v0, $v0, 8            #$v0 has 12, read char.
          syscall
          add $t0, $zero, $v0            #char read now in $t0

          addi $v0, $zero, 9            #calling sbrk
          addi $a0, $zero, 4
          syscall
          add $t1, $zero, $v0
          sb $t0, 0($t1)

          lui $a0, 80                #load str3 addr to $a0 and print.
          ori $a0, $a0, 60
          addi $v0, $zero, 4
          syscall

          lb $a0, 0($t1)
          addi $v0, $v0, 7            #print char
          syscall



      ############################################


          addi $a0,$zero, 80            #print str4
          sll $a0, $a0, 20
          srl $a0, $a0, 4
          ori $a0, $a0, 88
          addi $v0, $zero, 4
          syscall


          lui $a0, 80                #print str5
          ori $a0, $a0, 108
          addi $v0, $zero, 4
          syscall

          lui $a0, 80                #print str6
          ori $a0, $a0, 112
          addi $v0, $zero, 4
          syscall

          lui $a0, 80                #print str7
          ori $a0, $a0, 116
          addi $v0, $zero, 4
          syscall

          lui $a0, 80                #print str13
          ori $a0, $a0, 248
          addi $v0, $zero, 4
          syscall

      ############################################

          lui $a0, 80                #print str8
          ori $a0, $a0, 120
          addi $v0, $zero, 4
          syscall

          lui $a0, 80                #open file
          ori $a0, $a0, 148
          addi $a1, $zero, 2
          addi $v0, $v0, 9
          syscall

          add $t0, $zero, $v0        #transfer the file descriptor to $t0
          addi $v0, $zero, 9            #sbrk
          addi $a0, $zero, 60
          syscall

          add $t1, $zero, $v0    #transfer the allocated mem to $t1

          add $a0, $t0, $zero        #write str10 to file
          lui $a1, 80
          ori $a1, $a1, 164
          addi $a2, $zero, 40
          addi $v0, $zero, 15
          syscall

          add $t2, $zero, $v0     #transfer the num of chars written to $t2

          lui $a0, 80                #print str11
          ori $a0, $a0, 208
          addi $v0, $zero, 4
          syscall

          add $a0, $zero, $t2    #print num of chars written to file
          addi $t5, $zero, 3
          sub $v0, $v0, $t5
          syscall

          addi $v0, $zero, 16        #close file
          add $a0, $zero, $t0
          syscall

          lui $a0, 80                #open the file again
          ori $a0, $a0, 148
          addi $a1, $zero, 2
          addi $v0, $zero, 13
          syscall

          addi $a0, $t0, 0        #read from the file
          addi $a1, $t1, 0
          addi $a2, $zero, 41
          addi $v0, $zero, 14
          syscall

          addi $v0, $zero, 16        #close file
          add $a0, $zero, $t0
          syscall

          add $a0, $zero, $t1        #print the content read from file
          addi $v0, $zero, 4
          syscall





      ############################################
          lui $a0, 80                #print str14
          ori $a0, $a0, 316
          addi $v0, $zero, 4
          syscall

          lui $t0, 80            #load half array
          ori $t0, $t0, 308


          lui $a0, 80                #print str15
          ori $a0, $a0, 340
          addi $v0, $zero, 4
          syscall

          lh $a0, 0($t0)
          sll $a0, $a0, 16
          lh $t2, 2($t0)
          or $a0, $a0,$t2

          addi $a0, $a0, 1
          addi $v0, $zero, 1
          syscall


          lui $a0, 80                #print str16
          ori $a0, $a0, 404
          addi $v0, $zero, 4
          syscall


          lui $t1, 80                #load byte array
          ori $t1, $t1, 312

          lb $t2, 0($t1)
          sll $t2, $t2, 24
          lb $t3, 1($t1)
          sll $t3, $t3, 16
          lb $t4, 2($t1)
          sll $t4, $t4, 8
          lb $t5, 3($t1)

          or $a0, $t2,$t3
          or $a0, $a0,$t4
          or $a0, $a0,$t5

          addi $a0, $a0, -1
          addi $v0, $zero, 1
          syscall


      ############################################



          lui $a0, 80                #print str12
          ori $a0, $a0, 240
          addi $v0, $zero, 4
          syscall

          addi $v0, $zero, 10            #exit
          syscall
    )");
    std::istringstream in("5");
    std::ostringstream out;
    std::string ans("Testing lb,sb,read/print_char,sbrkPlease enter a char:"
                    "The char you entered is:5"
                    "Testing for .asciiaaaabbbbcccbbbbcccccc"
                    "You should see aaaabbbbccc, bbbbccc, ccc for three strings"
                    "Testing for fileIO syscalls"
                    "num of chars printed to file:40"
                    "If you see this, your fileIO is all cool"
                    "Testing for .half,.byte"
                    "For half, the output should be: 65539 in decimal, and you have:65539"
                    "For byte, the output should be: 16909059 in decimal, and you have:16909059"
                    "Goodbye");
    std::string file_ans("If you see this, your fileIO is all cool");
    std::string file_name("_tmp_file.txt");
    std::ofstream o_file(file_name);
    auto [mem, text_end] = assemble(asm_in);
    try {
        simulate(in, out, std::move(mem), text_end);
    } catch (const ExitError& e) {
        EXPECT_EQ(e.code(), 0);  // prevent folding
    }
    std::ifstream i_file(file_name);
    EXPECT_EQ(out.str(), ans);
    EXPECT_EQ(std::string(std::istreambuf_iterator<char>(i_file), std::istreambuf_iterator<char>{}),
              file_ans);
    std::filesystem::remove(file_name);
}
