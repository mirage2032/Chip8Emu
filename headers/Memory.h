//
// Created by nuvai on 07/12/2022.
//

#ifndef CHIP8EMU_MEMORY_H
#define CHIP8EMU_MEMORY_H

#include <fstream>
#include <cstdint>

class Memory {
private:
    uint8_t *mem;
public:
    Memory();

    void Set8(uint16_t pos,uint8_t val);
    void Set16(uint16_t pos,uint16_t val);
    uint16_t Get(uint16_t pos);
    void LoadRom(const char* rom_path);
    void* GetPtr(uint16_t pos);
    ~Memory();

};


#endif //CHIP8EMU_MEMORY_H
