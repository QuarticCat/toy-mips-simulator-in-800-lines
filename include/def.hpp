#pragma once

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <new>
#include <string_view>

// lovely Rust-style naming <3
using i64 = int64_t;
using u64 = uint64_t;
using i32 = int32_t;
using u32 = uint32_t;
using i16 = int16_t;
using u16 = uint16_t;
using u8 = uint8_t;
using i8 = int8_t;

inline constexpr u32 text_low = 0x400000;
inline constexpr u32 data_low = 0x500000;
inline constexpr u32 heap_low = 0x600000;  // ?
inline constexpr u32 stack_high = 0xa00000;

using Token = std::string_view;

/// Aligned 6 MiB u8 array for easier memory magic.
struct Memory: std::unique_ptr<u8[]> {
    Memory(): std::unique_ptr<u8[]>(new (std::align_val_t(4)) u8[stack_high - text_low]) {}
};
