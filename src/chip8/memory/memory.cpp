//
// Created by nuvai on 07/12/2022.
//

#include <cstring>
#include "memory.h"

Memory::Memory() {
    mem = new uint8_t[4096];
    memset(mem, 0, 4096);
    //DEFAULT HEX FONT starting at 0x50, ending at 0x9f
    uint8_t characters[] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                            0x20, 0x60, 0x20, 0x20, 0x70, // 1
                            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    std::memcpy(&mem[0x50], characters, 80);
}

void Memory::Set(uint16_t pos, uint8_t val) {
    mem[pos] = val;
}

void *Memory::Get(uint16_t pos) {
    return &(mem[pos]);
}

void Memory::LoadRom(const std::string &rom_path) {
    std::ifstream file;
    file.open(rom_path, std::ios_base::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open ROM file.");
    }

    file.seekg(0, std::ios::end);
    long size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (!file.read(reinterpret_cast<char *>(&mem[0x200]), size)) {
        file.close();
        throw std::runtime_error("Failed to read ROM file.");
    }

    file.close();
}

Memory::~Memory() {
    delete[] mem;
}
