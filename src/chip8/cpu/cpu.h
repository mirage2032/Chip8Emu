//
// Created by nuvai on 07/12/2022.
//

#ifndef CHIP8EMU_CPU_H
#define CHIP8EMU_CPU_H

#include "cstdint"
#include "stack.h"
#include "../io/io.h"
#include "../memory/Memory.h"
#include "../timer/timer.h"

class Cpu {
private:
    uint16_t pc = 0x200;
    uint16_t i = 0x200;
    Stack stack;
    Timer *del_timer;
    uint8_t snd_timer = 0;
    uint8_t registers[0x10];
    Io *io;
    Memory *memory;
    bool paused = false;
public:
    Cpu(Io *io, Memory *memory);

    void Execute();

    void Run();

    ~Cpu();
};


#endif //CHIP8EMU_CPU_H
