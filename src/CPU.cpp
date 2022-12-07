//
// Created by nuvai on 07/12/2022.
//

#include "../headers/CPU.h"

CPU::CPU(Display *dsp, Memory *mem){
    display = dsp;
    memory = mem;

}

void CPU::Run(){
    while(!paused){
        Execute();
    }
}
