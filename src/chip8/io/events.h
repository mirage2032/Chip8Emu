//
// Created by alx on 6/14/23.
//

#ifndef CHIP8EMU_EVENTS_H
#define CHIP8EMU_EVENTS_H

#include <SDL2/SDL_events.h>

class Events {
    SDL_Event e;
public:

    void HandleEvents();

    bool GetKey(uint8_t key);
    uint8_t WaitKey();
};

#endif //CHIP8EMU_EVENTS_H
