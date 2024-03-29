//
// Created by alx on 6/14/23.
//

#ifndef CHIP8EMU_DISPLAY_H
#define CHIP8EMU_DISPLAY_H
#include <SDL2/SDL.h>

class Display {
private:
    bool *pixels;
    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    void ClearScreen();
public:
    explicit Display();
    void ClearPixels();
    uint8_t Draw(uint8_t x, uint8_t y, const uint8_t *memloc, uint8_t count, bool clipping);
    void Render();
    ~Display();
};


#endif //CHIP8EMU_DISPLAY_H
