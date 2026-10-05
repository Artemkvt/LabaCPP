#include "cpu.hpp"

#include <iostream>

#include "alu.hpp"

namespace {

struct DecodedOpcode {
    Byte group;
    Byte index;
};

DecodedOpcode decode(Byte instruction) {
    const Byte group = static_cast<Byte>((instruction >> 4) & 0x0F);
    const Byte dest = static_cast<Byte>((instruction >> 2) & 0x03);
    const Byte src = static_cast<Byte>(instruction & 0x03);
    const Byte index = static_cast<Byte>((dest << 2) | src);
    return {group, index};
}

}  // namespace

void dump_regs(const CPU& cpu) {
    std::cout << "PC=" << cpu.pc
              << " A=" << static_cast<int>(cpu.a)
              << " B=" << static_cast<int>(cpu.b)
              << " Z=" << cpu.f.z
              << " N=" << cpu.f.n
              << " C=" << cpu.f.c
              << '\n';
}

void step(CPU& cpu) {
    if (cpu.halted) {
        std::cout << "halted\n";
        return;
    }

    const DecodedOpcode decoded = decode(mem_get(*cpu.mem, cpu.pc));

    switch (decoded.group) {
    case 0x0:
        switch (decoded.index) {
        case 0x0:
            cpu.halted = true;
            cpu.pc += 1;
            break;
        case 0x1:
            cpu.pc += 1;
            break;
        default:
            cpu.pc += 1;
            break;
        }
        break;

    case 0x1:
        switch (decoded.index) {
        case 0x0:
            cpu.a = alu_add(cpu.a, cpu.b, cpu.f);
            break;
        case 0x1:
            cpu.a = alu_sub(cpu.a, cpu.b, cpu.f);
            break;
        case 0x2:
            cpu.a = alu_and(cpu.a, cpu.b, cpu.f);
            break;
        case 0x3:
            cpu.a = alu_or(cpu.a, cpu.b, cpu.f);
            break;
        case 0x4:
            cpu.a = alu_xor(cpu.a, cpu.b, cpu.f);
            break;
        case 0x5:
            cpu.a = alu_not(cpu.a, cpu.f);
            break;
        case 0x6:
            cpu.a = alu_shl(cpu.a, cpu.b, cpu.f);
            break;
        case 0x7:
            cpu.a = alu_shr(cpu.a, cpu.b, cpu.f);
            break;
        case 0x8:
            cpu.a = alu_inc(cpu.a, cpu.f);
            break;
        case 0x9:
            cpu.a = alu_dec(cpu.a, cpu.f);
            break;
        default:
            break;
        }
        cpu.pc += 1;
        break;

    default:
        cpu.pc += 1;
        break;
    }
}