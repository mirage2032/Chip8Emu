//
// Created by nuvai on 07/12/2022.
//

#include "../headers/Display.h"
#define WIDTH 64
#define HEIGHT 32
#define SCALE 10
Display::Display() {
    pixels = new bool[64 * 32];
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    SDL_RenderSetScale(renderer, SCALE, SCALE);
    SDL_SetWindowSize(window, WIDTH*SCALE, HEIGHT*SCALE);
    Clear();
}

void Display::Clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

uint16_t Display::Draw(uint8_t x, uint8_t y, const uint8_t *memloc, uint8_t count) {
    uint16_t vf = 0;
    for (int curyoffset = 0; curyoffset < count; curyoffset++) {
        for (int curxoffset = 0; curxoffset < 8; curxoffset++) {
            bool *current_pixel = &pixels[((x + curxoffset)%64) + 64 * ((y + curyoffset)%32)];
            if(memloc[curyoffset] & (1 << (7 - curxoffset))) {
                if (*current_pixel)
                    vf = 1;
                *current_pixel = !*current_pixel;
            }
        }
    }
    Render();
    return vf;
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
    SDL_RenderPresent(renderer);
}

Display::~Display() {
    delete[] pixels;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
