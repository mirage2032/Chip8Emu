//
// Created by nuvai on 07/12/2022.
//

#ifndef CHIP8EMU_IO_H
#define CHIP8EMU_IO_H

#include <cstdint>
#include <SDL2/SDL.h>
#include "display.h"
#include "events.h"

class Io {
public:
    Display display;
    Events events;
    Io();
    ~Io();
};


#endif //CHIP8EMU_IO_H
