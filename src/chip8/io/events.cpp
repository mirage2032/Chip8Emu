//
// Created by alx on 6/14/23.
//
#include <vector>
#include <iostream>
#include "events.h"

SDL_Scancode keyboardLut[0x10] = {SDL_SCANCODE_KP_0,
                                  SDL_SCANCODE_KP_1,
                                  SDL_SCANCODE_KP_2,
                                  SDL_SCANCODE_KP_3,
                                  SDL_SCANCODE_KP_4,
                                  SDL_SCANCODE_KP_5,
                                  SDL_SCANCODE_KP_6,
                                  SDL_SCANCODE_KP_7,
                                  SDL_SCANCODE_KP_8,
                                  SDL_SCANCODE_KP_9,
                                  SDL_SCANCODE_A,
                                  SDL_SCANCODE_B,
                                  SDL_SCANCODE_C,
                                  SDL_SCANCODE_D,
                                  SDL_SCANCODE_E,
                                  SDL_SCANCODE_F,
};

void Events::HandleEvents() {
    while (SDL_PollEvent(&e) != 0) {
        // Quit event (e.g., window close button)
        if (e.type == SDL_QUIT) {
            //TODO:Handle exit
        }
    }
}

bool Events::GetKey(uint8_t key) {
    HandleEvents();
    const uint8_t *currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (currentKeyStates[keyboardLut[key]])
        return true;
    return false;
}

uint8_t Events::WaitKey() {
    while (true) {
        for (uint8_t i = 0; i < 0x10; i++){
            bool isPressed = GetKey(i);
            if(isPressed)
                return i;
        }
    }
}

