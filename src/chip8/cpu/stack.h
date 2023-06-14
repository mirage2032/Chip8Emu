//
// Created by alx on 07.12.2022.
//

#ifndef CHIP8EMU_STACK_H
#define CHIP8EMU_STACK_H

#include "cstdint"
#include "cstdlib"

class Stack {
private:
    int current_size=0;
    int max_size=32;
    uint16_t* stack;
public:
    Stack();
    void Push(uint16_t val);
    uint16_t Pop();
    ~Stack();
};


#endif //CHIP8EMU_STACK_H
