# Chip8Emu

This is a Chip8 emulator created in C++.

## Compatiblity

This emulator is compatible with both Windows and Linux systems.

## Usage

1. Build the project, alternatively you can download it from the Releases page.

If you're building the project from source make sure to use `--recurse-submodules`  when cloning it.

`git clone --recurse-submodules https://github.com/mirage2032/Chip8Emu.git`

This is needed as it uses SDL2 as a submodule in order to build it as a static library link against it.

If you're downloading the project from the Releases page make sure to download the correct one depending on the
operating system you're using.

`Chip8Emu` for Linux based systems and `Chip8Emu.exe` for Windows.

4. Create a `/roms` directory in the same directory
3. Place all the Chip8 roms inside the `/roms ` directory
4. Launch the executable
5. Choose rom

## Dependencies

The only dependency of this project is SDL2.

## To do:

- Add sound
- Make the button to close the window work. At the momment it can be stopped only by killing the process

## To fix:

- Fix quirks
    - Display wait - not implemented
    - Clipping - not fully working