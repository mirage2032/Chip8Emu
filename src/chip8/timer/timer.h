//
// Created by alx on 6/14/23.
//

#ifndef CHIP8EMU_TIMER_H
#define CHIP8EMU_TIMER_H

#include <atomic>
#include <thread>
class Timer {
private:
    int frequency;
    std::atomic<uint8_t> timer;
    bool stopFlag = false;
    std::thread timerThread;

    void start();
    void decrementTimer();
    void stop();

public:
    explicit Timer(int frequency);
    void Set(uint8_t value);

    uint8_t Get();
    ~Timer();
};


#endif //CHIP8EMU_TIMER_H
