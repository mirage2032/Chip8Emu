//
// Created by alx on 6/14/23.
//

#include <thread>
#include <chrono>
#include "timer.h"


void Timer::decrementTimer() {
    {
        while (timer > 0 && !stopFlag) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000000 / frequency));
            timer--;
        }
        timerThread.detach();
    }
}

void Timer::start() {
    stopFlag = false;
    timerThread = std::thread(&Timer::decrementTimer, this);
}

Timer::Timer(int frequency) : frequency(frequency), timer(0) {}

void Timer::Set(uint8_t value) {
    timer = value;
    if(!timerThread.joinable())
        start();
}

uint8_t Timer::Get() {
    return timer;
}

Timer::~Timer() {
    if (timerThread.joinable()) {
        stopFlag = true;
        timerThread.join();
    }
}




