//
// Created by alx on 07.12.2022.
//

#include "../headers/CPU.h"
#include "iostream"

void CPU::Execute() {
    auto *instruction = (uint16_t *) memory->GetPtr(pc);
    uint16_t instr = (*instruction >> 8) | (*instruction << 8);
    pc += 2;
    uint32_t tmp;
    uint16_t vx = (instr & 0x0F00) >> 8;
    uint16_t vy = (instr & 0x00F0) >> 4;
    uint16_t n = instr & 0x000F;
    uint16_t nn = instr & 0x00FF;
    uint16_t nnn = instr & 0x0FFF;


    switch (instr & 0xF000) {
        case 0x0000:
            if (instr == 0x00E0) //CLS
                display->Clear();
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
                    break;
                case 0x2: //AND Vx, Vy
                    registers[vx] = registers[vx] & registers[vy];
                    break;
                case 0x3: //XOR Vx, Vy
                    registers[vx] = registers[vx] ^ registers[vy];
                    break;
                case 0x4: //ADD Vx, Vy
                    tmp = registers[vx] + registers[vy];
                    if (tmp > 0xFF)
                        registers[0xF] = 1;
                    registers[vx] = tmp;
                    break;
                case 0x5: //SUB Vx, Vy
                    registers[vx] = registers[vx] - registers[vy];
                    if (registers[vx] > registers[vy])
                        registers[0xF] = 1;
                    break;
                case 0x6: //SHR Vx {, Vy}
                    if (registers[vx] & 0b1)
                        registers[0xF] = 1;
                    registers[vx] = registers[vx] >> 1;
                    break;
                case 0x7: //SUBN Vx, Vy
                    registers[vx] = registers[vy] - registers[vx];
                    if (registers[vy] > registers[vx])
                        registers[0xF] = 1;
                    break;
                case 0xE: //SHL Vx {, Vy}
                    if (registers[vx] & 0b1)
                        registers[0xF] = 1;
                    registers[vx] = registers[vx] << 1;
                    break;
                default:
                    std::cout<< std::hex << instr << " ERROR\n";
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
            registers[vx] = rand() % 256 & nn;
            break;
        case 0xD000: //DRW Vx, Vy, nibble
            registers[0xF] = display->Draw(registers[vx], registers[vy], (uint8_t *) memory->GetPtr(i), n);
            break;
        case 0xE000://TODO:Input
            switch (nn) {
                case 0x9E: //SKP Vx
                    break;
                case 0xA1: //SKNP Vx
                    pc += 2;
                    break;
                default:
                    std::cout << std::hex << instr << " ERROR:\n" ;
            }
            break;
        case 0xF000:
            switch (nn) {
                case 0x07: //LD Vx, DT
                    registers[vx] = del_timer;
                    break;
                case 0x0A: //LD Vx, K
                    std::cout << "KEY=";
                    std::cin >> tmp;
                    registers[vx] = tmp;
                    break;
                case 0x15: //LD DT, Vx
                    del_timer = registers[vx];
                case 0x18: //LD ST, Vx
                    snd_timer = registers[vx];
                case 0x1E: //ADD I, Vx
                    i = i + registers[vx];
                    break;
                case 0x29: //LD F, Vx
                    i = 50 + vx * 5;
                    break;
                case 0x33: //LD B, Vx
                    tmp = registers[vx];
                    memory->Set8(i + 2, tmp % 10);
                    tmp /= 10;
                    memory->Set8(i + 1, tmp % 10);
                    tmp /= 10;
                    memory->Set8(i, tmp % 10);
                    break;
                case 0x55: //LD [I], Vx
                    memcpy(memory->GetPtr(i), registers, vx+1);
                    break;
                case 0x65: //LD Vx, [I]
                    memcpy(registers, memory->GetPtr(i), vx+1);
                    break;
                default:
                    std::cout << std::hex<< instr << " ERROR:\n";
            }
            break;
        default:
            std::cout<< std::hex<< instr << " ERROR:\n";
    }
}
