#include <iostream>
#include "chip8/cpu/cpu.h"

int main() {
    srand(time(nullptr));
    auto *dsp = new Io;
    auto *mem = new Memory;
    mem->LoadRom("../testroms/4-flags.ch8");
    auto *cpu = new Cpu(dsp, mem);
    cpu->Run();
}
