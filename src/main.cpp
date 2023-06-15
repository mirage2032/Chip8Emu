#include <iostream>
#include <vector>
#include <filesystem>
#include "chip8/cpu/cpu.h"

std::string chooseRom(std::string romsdir) {
    if (!std::filesystem::is_directory(romsdir))
        throw std::runtime_error("\nThe roms directory " + romsdir + " does not exist.\nPlease create it.\n");
    auto roms = std::vector<std::filesystem::path>();
    for (const auto &entry: std::filesystem::directory_iterator(romsdir)) {
        roms.push_back(entry);
    }
    if (roms.empty())
        throw std::runtime_error("\nThe roms directory " + romsdir + " is empty.\nPlease add at least a rom in it.\n");
    for (int i = 0; i < roms.size(); i++) {
        std::cout << i + 1 << ") " << roms[i] << std::endl;
    }
    unsigned int romindex = 0;
    while (romindex == 0 || romindex > roms.size()) {
        std::cout << "Choose rom: ";
        std::cin >> romindex;
    }
    return roms[romindex - 1];
}

int main() {
    auto romPath = chooseRom("./roms");
    auto *io = new Io;
    auto *mem = new Memory;
    mem->LoadRom(romPath);
    auto *cpu = new Cpu(io, mem);
    cpu->Run();
}
