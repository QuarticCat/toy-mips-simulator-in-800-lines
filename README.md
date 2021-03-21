# Toy MIPS Simulator in 800 Lines

A super short and clean toy MIPS simulator.

## Support

Too lazy to list all details.

### Assembler Directives

- `.ascii`
- `.asciiz`
- `.word`
- `.half`
- `.byte`

### Instructions

See [instr.hpp](/include/instr.hpp).

No delay slot. No coprocessor. No floating-point.

### Syscalls

See [simulator.hpp](/include/simulator.hpp).

### Memory

6 MiB in total, from 0x400000 to 0xa00000.

Text segment starts at 0x400000.

Data segment starts at 0x500000.

Stack segment starts at 0xa00000.

## Requirements

- GCC >= 10.2 or Clang >= 11.1
- CMake >= 3.19
- Google Test (optional)

## Build & Run

```console
$ cd mips-simulator
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make
$ ./simulator <asm-file>
```

## Test

```console
$ cd mips-simulator
$ mkdir build
$ cd build
$ cmake .. -DSIM_BUILD_TESTS=On
$ make
$ ./sim_tests
```

Tests are mostly provided by [@Dranggo](https://github.com/huhaichuan0704).

## License

MIT
