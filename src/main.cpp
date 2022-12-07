#include <iostream>
#include "../headers/Memory.h"
#include "../headers/Display.h"

int main() {
    Display *dsp = new Display;
    Memory *mem = new Memory;
    dsp->Draw(1, 1, (uint8_t *) mem->GetPtr(0x50), 5);
    int x;
    std::cin >> x;
}
