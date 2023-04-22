#include <iostream>
#include "../headers/CPU.h"

int main() {
    srand(time(nullptr));
    auto *dsp = new Display;
    auto *mem = new Memory;
    mem->LoadRom("/home/alx/CLionProjects/Chip8Emu/test_opcode.ch8");
    auto *cpu = new CPU(dsp, mem);
    cpu->Run();
}
