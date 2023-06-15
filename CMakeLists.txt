cmake_minimum_required(VERSION 3.9)
project(Chip8Emu)

set(CMAKE_CXX_STANDARD 23)

# Set the path to the SDL source directory
set(SDL2_SOURCE_DIR "dep/SDL")

# Build SDL from source
add_subdirectory(${SDL2_SOURCE_DIR} ${SDL2_BINARY_DIR})

include_directories(
        "${SDL2_SOURCE_DIR}/include"
)

add_executable(Chip8Emu
        src/main.cpp
        src/chip8/cpu/cpu.cpp
        src/chip8/cpu/cpu.h
        src/chip8/memory/memory.cpp
        src/chip8/memory/memory.h
        src/chip8/io/io.cpp
        src/chip8/io/io.h
        src/chip8/cpu/stack.cpp
        src/chip8/cpu/stack.h
        src/chip8/cpu/instruction.cpp
        src/chip8/io/display.cpp
        src/chip8/io/display.h
        src/chip8/io/events.cpp
        src/chip8/io/events.h
        src/chip8/timer/timer.cpp
        src/chip8/timer/timer.h
        )

add_definitions(-DSDL_MAIN_HANDLED)

# Link against SDL2 libraries
target_link_libraries(Chip8Emu PRIVATE
        SDL2-static
        SDL2main
        )
