//
// Created by nuvai on 07/12/2022.
//

#include "../headers/Display.h"


Display::Display() {
    pixels = new bool[64 * 32];
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(64, 32, 0, &window, &renderer);

    SDL_RenderSetScale(renderer, 2, 2);
    SDL_SetWindowSize(window, 128, 64);
}

void Display::Clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Display::Draw(uint8_t x, uint8_t y, const uint8_t *memloc, uint8_t count) {
    for (int curyoffset = 0; curyoffset < count; curyoffset++) {
        for (int curxoffset = 0; curxoffset < 8; curxoffset++) {
            bool *current_pixel = &pixels[x + curxoffset + 64 * (y + curyoffset)];
            *current_pixel = memloc[curyoffset] & (1 << (8 - curxoffset)); //set pixel
        }
    }
}

void Display::Render() {
    Clear();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (pixels[x + 64 * y])
                SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

Display::~Display() {
    delete[] pixels;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
