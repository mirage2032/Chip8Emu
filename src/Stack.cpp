//
// Created by alx on 07.12.2022.
//

#include "../headers/Stack.h"

Stack::Stack() {
    stack = (uint16_t*)malloc(max_size*sizeof(uint16_t));
}

void Stack::Push(uint16_t val) {
    stack[current_size] = val;
    current_size++;
    if(current_size==max_size)
    {
        max_size+=32;
        stack = (uint16_t*)realloc(stack,max_size*sizeof(uint16_t));
    }
}

uint16_t Stack::Pop() {
    if(current_size==0){
        abort(); //TODO except handler
    }
    current_size--;
    return stack[current_size+1];
}

Stack::~Stack() {
    free(stack);
}
