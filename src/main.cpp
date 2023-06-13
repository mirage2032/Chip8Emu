#include <iostream>
#include "../headers/CPU.h"

int main() {
    srand(time(nullptr));
    auto *dsp = new Display;
    auto *mem = new Memory;
    mem->LoadRom("/home/alx/CLionProjects/Chip8Emu/testroms/3-corax+.ch8");
    auto *cpu = new CPU(dsp, mem);
    cpu->Run();
}
