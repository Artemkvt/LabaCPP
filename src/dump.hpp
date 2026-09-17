// dump.hpp — two ways of looking at bytes.
// GIVEN.
#pragma once

#include "memory.hpp"

// Print the whole box, 16 bytes per line: address, hex, ASCII gutter.
void dump(const Memory& mem);

void show_byte(Byte b);
