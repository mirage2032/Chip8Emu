//
// Created by nuvai on 07/12/2022.
//

#ifndef CHIP8EMU_DISPLAY_H
#define CHIP8EMU_DISPLAY_H

#include <cstdint>
#include "SDL2/sdl.h"

class Display {
private:
    bool *pixels;
    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
public:
    Display();

    void Clear();
    void Draw(uint8_t x, uint8_t y, const uint8_t *memloc, uint8_t count);
    void Render();

    ~Display();

};


#endif //CHIP8EMU_DISPLAY_H
