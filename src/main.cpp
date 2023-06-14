#include <iostream>
#include "chip8/cpu/cpu.h"

int main() {
    auto *dsp = new Io;
    auto *mem = new Memory;
    mem->LoadRom("../testroms/Bowling.ch8");
    auto *cpu = new Cpu(dsp, mem);
    cpu->Run();
}
