#pragma once

#include <bitset>
#include <sstream>
#include <string>

#include "assembler.hpp"
#include "gtest/gtest.h"
#include "simulator.hpp"

#define ASM_TEST(test_suite_name, test_name, in_str, out_str) \
    TEST(test_suite_name, test_name) {                        \
        std::istringstream asm_in(in_str);                    \
        std::string ans(out_str);                             \
        std::ostringstream out;                               \
        auto [mem, text_end] = assemble(asm_in);              \
        for (size_t i = 0; i < text_end - text_low; i += 4)   \
            out << std::bitset<32>((u32&)mem[i]) << '\n';     \
        EXPECT_EQ(out.str(), ans);                            \
    }                                                         \
    static_assert(true)

#define SIM_TEST(test_suite_name, test_name, asm_in_str, in_str, out_str) \
    TEST(test_suite_name, test_name) {                                    \
        std::istringstream asm_in(asm_in_str);                            \
        std::istringstream in(in_str);                                    \
        std::string ans(out_str);                                         \
        std::ostringstream out;                                           \
        auto [mem, text_end] = assemble(asm_in);                          \
        try {                                                             \
            simulate(in, out, std::move(mem), text_end);                  \
        } catch (const ExitError& e) {                                    \
            /* prevent folding */                                         \
            EXPECT_EQ(e.code(), 0);                                       \
        }                                                                 \
        EXPECT_EQ(out.str(), ans);                                        \
    }                                                                     \
    static_assert(true)

#define SIM_TRAP_TEST(test_suite_name, test_name, asm_in_str, in_str, out_str) \
    TEST(test_suite_name, test_name) {                                         \
        std::istringstream asm_in(asm_in_str);                                 \
        std::istringstream in(in_str);                                         \
        std::string ans(out_str);                                              \
        std::ostringstream out;                                                \
        auto [mem, text_end] = assemble(asm_in);                               \
        EXPECT_THROW(simulate(in, out, std::move(mem), text_end), TrapError);  \
        EXPECT_EQ(out.str(), ans);                                             \
    }                                                                          \
    static_assert(true)

#define SIM_EXIT_TEST(test_suite_name, test_name, asm_in_str, in_str, out_str) \
    TEST(test_suite_name, test_name) {                                         \
        std::istringstream asm_in(asm_in_str);                                 \
        std::istringstream in(in_str);                                         \
        std::string ans(out_str);                                              \
        std::ostringstream out;                                                \
        auto [mem, text_end] = assemble(asm_in);                               \
        EXPECT_THROW(simulate(in, out, std::move(mem), text_end), ExitError);  \
        EXPECT_EQ(out.str(), ans);                                             \
    }                                                                          \
    static_assert(true)
