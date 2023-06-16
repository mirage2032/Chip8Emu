//
// Created by alx on 07.12.2022.
//

#include <iostream>
#include <cstring>
#include <random>
#include "cpu.h"

void printUnknownInstruction(uint16_t instruction) {
    std::cout << std::hex << instruction << " ERROR\n";
}

uint8_t randuint8(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> dis(0, std::numeric_limits<uint8_t>::max());
    return static_cast<uint8_t>(dis(gen));
}

uint8_t checkCarry(uint32_t val) {
    if (val > 0xFF)
        return 1;
    return 0;
}

void Cpu::Execute() {
    auto *instruction = (uint16_t *) memory->Get(pc);
    uint16_t instr = (*instruction >> 8) | (*instruction << 8);
    pc += 2;
    uint32_t tmp;
    uint16_t vx = (instr & 0x0F00) >> 8;
    uint16_t vy = (instr & 0x00F0) >> 4;
    uint8_t n = instr & 0x000F;
    uint8_t nn = instr & 0x00FF;
    uint16_t nnn = instr & 0x0FFF;


    switch (instr & 0xF000) {
        case 0x0000:
            if (instr == 0x00E0) //CLS
                io->display.ClearPixels();
            if (instr == 0x00EE) //RET
                pc = stack.Pop();
            break;
        case 0x1000: //JP addr
            pc = nnn;
            break;
        case 0x2000: //CALL addr
            stack.Push(pc);
            pc = nnn;
            break;
        case 0x3000: //SE Vx, byte
            if ((registers[vx] & (0xFF)) == nn)
                pc += 2;
            break;
        case 0x4000: //SNE Vx, byte
            if ((registers[vx] & (0xFF)) != nn)
                pc += 2;
            break;
        case 0x5000: //SE Vx, Vy
            if (registers[vx] == registers[vy])
                pc += 2;
            break;
        case 0x6000: //LD Vx, byte
            registers[vx] = nn;
            break;
        case 0x7000: //ADD Vx, byte
            registers[vx] += nn;
            break;
        case 0x8000:
            switch (n) {
                case 0x0: //LD Vx, Vy
                    registers[vx] = registers[vy];
                    break;
                case 0x1: //OR Vx, Vy
                    registers[vx] = registers[vx] | registers[vy];
                    registers[0xF] = 0x0; //Chip-8 quirk vF reset
                    break;
                case 0x2: //AND Vx, Vy
                    registers[vx] = registers[vx] & registers[vy];
                    registers[0xF] = 0x0; //Chip-8 quirk vF reset
                    break;
                case 0x3: //XOR Vx, Vy
                    registers[vx] ^= registers[vy];
                    registers[0xF] = 0x0; //Chip-8 quirk vF reset
                    break;
                case 0x4: //ADD Vx, Vy
                    tmp = registers[vx] + registers[vy];
                    registers[vx] = tmp;
                    if (tmp > 0xFF)
                        registers[0xF] = 1;
                    else
                        registers[0xF] = 0;
                    break;
                case 0x5: // SUB Vx, Vy
                    tmp = registers[vx] - registers[vy];
                    registers[vx] = tmp;
                    if (tmp > 0xFF)
                        registers[0xF] = 0;
                    else
                        registers[0xF] = 1;
                    break;
                case 0x6: //SHR Vx {, Vy}
                    registers[vx] = registers[vy]; //Chip-8 quirk SHIFTING
                    if (registers[vx] & 0b1)
                        tmp = 1;
                    else
                        tmp = 0;
                    registers[vx] = registers[vx] >> 1;
                    registers[0xF] = tmp;
                    break;
                case 0x7: //SUBN Vx, Vy
                    if (registers[vy] > registers[vx]) //Chip-8 quirk SHIFTING
                        tmp = 1;
                    else
                        tmp = 0;
                    registers[vx] = registers[vy] - registers[vx];
                    registers[0xF] = tmp;
                    break;
                case 0xE: //SHL Vx {, Vy}
                    registers[vx] = registers[vy];
                    if (registers[vx] & 0b10000000) // Check if MSB is 1 (carry condition)
                        tmp = 1;
                    else
                        tmp = 0;
                    registers[vx] = registers[vx] << 1;
                    registers[0xF] = tmp;
                    break;
                default:
                    printUnknownInstruction(instr);
            }
            break;
        case 0x9000: //SNE Vx, Vy
            if (registers[vx] != registers[vy])
                pc += 2;
            break;
        case 0xA000: //LD I, addr
            i = nnn;
            break;
        case 0xB000: //JP V0, addr
            pc = nnn + registers[0];
            break;
        case 0xC000: //RND Vx, byte
            registers[vx] = randuint8() & nn;
            break;
        case 0xD000: //DRW Vx, Vy, nibble
            registers[0xF] = io->display.Draw(registers[vx], registers[vy], (uint8_t *) memory->Get(i), n, true);
            break;
        case 0xE000:
            switch (nn) {
                case 0x9E: //SKP Vx
                    if (io->events.GetKey(registers[vx]))
                        pc += 2;
                    break;
                case 0xA1: //SKNP Vx
                    if (!io->events.GetKey(registers[vx]))
                        pc += 2;
                    break;
                default:
                    printUnknownInstruction(instr);
            }
            break;
        case 0xF000:
            switch (nn) {
                case 0x07: //LD Vx, DT
                    registers[vx] = del_timer->Get();
                    break;
                case 0x0A: //LD Vx, K
                    registers[vx] = io->events.WaitKey();
                    break;
                case 0x15: //LD DT, Vx
                    del_timer->Set(registers[vx]);
                    break;
                case 0x18: //LD ST, Vx
                    snd_timer = registers[vx];
                    break;
                case 0x1E: //ADD I, Vx
                    i = i + registers[vx];
                    break;
                case 0x29: //LD F, Vx
                    i = 50 + vx * 5;
                    break;
                case 0x33: //LD B, Vx
                    tmp = registers[vx];
                    memory->Set(i + 2, tmp % 10);
                    tmp /= 10;
                    memory->Set(i + 1, tmp % 10);
                    tmp /= 10;
                    memory->Set(i, tmp % 10);
                    break;
                case 0x55: //LD [I], Vx
                    memcpy(memory->Get(i), registers, vx + 1);
                    i++; //Chip-8 quirk Memory
                    break;
                case 0x65: //LD Vx, [I]
                    memcpy(registers, memory->Get(i), vx + 1);
                    i++; //Chip-8 quirk Memory
                    break;
                default:
                    printUnknownInstruction(instr);
            }
            break;
        default:
            printUnknownInstruction(instr);
    }
}