#include <iostream>
#include "chip8/cpu/cpu.h"

int main() {
    auto *dsp = new Io;
    auto *mem = new Memory;
    std::string romPath;
    std::cout<< "Rom path: ";
    std::cin >> romPath;
    mem->LoadRom(romPath);
    auto *cpu = new Cpu(dsp, mem);
    cpu->Run();
}
