#include <fstream>
#include <iostream>
#include <string>

#include "assembler.hpp"
#include "simulator.hpp"

using namespace std::literals::string_literals;

int main(int argc, char* argv[]) {
    if (argc != 2) throw std::runtime_error("Wrong argument number!");

    std::ifstream asm_in(argv[1]);
    if (!asm_in.is_open()) throw std::runtime_error("File not found: "s + argv[1]);

    auto [mem, text_end] = assemble(asm_in);
    try {
        simulate(std::cin, std::cout, std::move(mem), text_end);
    } catch (const ExitError& e) {
        return e.code();  // prevent folding
    }
}
