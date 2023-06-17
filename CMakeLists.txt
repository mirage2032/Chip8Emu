cmake_minimum_required(VERSION 3.9)
project(Chip8Emu)

set(CMAKE_CXX_STANDARD 23)

# Set the path to the SDL source directory
set(SDL2_SOURCE_DIR "dep/SDL")

# Build SDL from source
add_subdirectory(${SDL2_SOURCE_DIR} ${SDL2_BINARY_DIR})

include_directories("${SDL2_SOURCE_DIR}/include")

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(Chip8Emu ${SOURCES})

add_definitions(-DSDL_MAIN_HANDLED)

# Link against SDL2 libraries
target_link_libraries(Chip8Emu PRIVATE
        SDL2-static
        SDL2main
        )
