//
// Created by nuvai on 07/12/2022.
//
#include <chrono>
#include <thread>
#include "cpu.h"

constexpr int CPU_FREQUENCY = 600;

Cpu::Cpu(Io *dsp, Memory *mem) {
    io = dsp;
    memory = mem;

}

void Cpu::Run() {
    constexpr auto frameDuration = std::chrono::microseconds(1000000 / CPU_FREQUENCY);
    while (!paused) {
        auto start_time = std::chrono::high_resolution_clock::now();

        Execute();

        auto end_time = std::chrono::high_resolution_clock::now();
        auto exec_time = end_time - start_time;
        auto remaining_time = frameDuration-exec_time;
        if(remaining_time>std::chrono::microseconds(0)){
            std::this_thread::sleep_for(remaining_time);
        }
    }
}
