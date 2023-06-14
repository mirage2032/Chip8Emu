cmake_minimum_required(VERSION 3.9)
project(Chip8Emu)
set(CMAKE_CXX_STANDARD 23)

add_executable(Chip8Emu src/main.cpp src/chip8/cpu/cpu.cpp src/chip8/cpu/cpu.h src/chip8/memory/memory.cpp src/chip8/memory/Memory.h src/chip8/io/io.cpp src/chip8/io/io.h src/chip8/cpu/stack.cpp src/chip8/cpu/stack.h src/chip8/cpu/instruction.cpp src/chip8/io/display.cpp src/chip8/io/display.h src/chip8/io/events.cpp src/chip8/io/events.h)
target_link_libraries(Chip8Emu -lSDL2)
add_definitions(-DSDL_MAIN_HANDLED)

