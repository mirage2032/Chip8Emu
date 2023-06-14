//
// Created by alx on 6/14/23.
//

#include "display.h"

constexpr uint8_t WIDTH = 64;
constexpr uint8_t HEIGHT = 32;
constexpr uint8_t SCALE = 10;
constexpr struct {
    SDL_Color ON = {255, 255, 255, 255};
    SDL_Color OFF = {40, 40, 40, 255};
} PIXEL_COLOR;

void Display::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, PIXEL_COLOR.OFF.r, PIXEL_COLOR.OFF.g, PIXEL_COLOR.OFF.b, PIXEL_COLOR.OFF.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

Display::Display() {
    pixels = new bool[WIDTH * HEIGHT];
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, SCALE, SCALE);
    SDL_SetWindowSize(window, WIDTH * SCALE, HEIGHT * SCALE);
    ClearScreen();
}

void Display::ClearPixels() {
    memset(pixels,0,WIDTH*HEIGHT);
    Render();
}

uint16_t Display::Draw(uint8_t x, uint8_t y, const uint8_t *memloc, uint8_t count, bool clipping) {
    uint16_t vf = 0;
    for (int curyoffset = 0; curyoffset < count; curyoffset++) {
        for (int curxoffset = 0; curxoffset < 8; curxoffset++) {

            // Apply clipping if enabled
            if (clipping && (x + curxoffset >= WIDTH || y + curyoffset >= HEIGHT))
                continue;

            int pixelX = (x + curxoffset) % WIDTH;
            int pixelY = (y + curyoffset) % HEIGHT;
            bool *current_pixel = &pixels[pixelX + WIDTH * pixelY];
            if (memloc[curyoffset] & (1 << (7 - curxoffset))) {
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
    ClearScreen();
    SDL_SetRenderDrawColor(renderer, PIXEL_COLOR.ON.r, PIXEL_COLOR.ON.g, PIXEL_COLOR.ON.b, PIXEL_COLOR.ON.a);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (pixels[x + WIDTH * y])
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
