cmake_minimum_required(VERSION 3.9)
project(Chip8Emu)
set(CMAKE_CXX_STANDARD 23)

add_executable(Chip8Emu src/main.cpp src/CPU.cpp headers/CPU.h src/Memory.cpp headers/Memory.h src/Display.cpp headers/Display.h src/Stack.cpp headers/Stack.h src/CPUInstruction.cpp)
target_link_libraries(Chip8Emu -lSDL2)
add_definitions(-DSDL_MAIN_HANDLED)

