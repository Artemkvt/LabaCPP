// memory.hpp — the box of bytes.
//
// GIVEN. You do not have to change this file in Lab 1, but read every line:
// four of the five ideas in Lab 1's theory are visible here.
#pragma once

#include <cstddef>
#include <cstdint>

// A cell of ember memory is exactly one byte, on every machine, forever.
// That is why it is std::uint8_t and not `int` (whose width is not promised).
using Byte = std::uint8_t;

// `const` means: this name will not be used to change these bits.
const std::size_t MEM_SIZE = 4096;

struct Memory {
    Byte data[MEM_SIZE]{};
};

Byte mem_get(const Memory& mem, std::size_t addr);
bool mem_set(Memory& mem, std::size_t addr, Byte value);
