cmake_minimum_required(VERSION 3.9)
project(Chip8Emu)
set(CMAKE_CXX_STANDARD 23)

add_executable(Chip8Emu src/main.cpp src/CPU.cpp headers/CPU.h src/Memory.cpp headers/Memory.h src/Display.cpp headers/Display.h)

target_link_libraries(Chip8Emu ${SDL2_LIBRARY})
add_definitions(-DSDL_MAIN_HANDLED)
