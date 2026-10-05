#include "alu.hpp"

#include <cstdint>

static void update_flags(Byte result, bool carry, Flags& f) {
    f.z = (result == 0);
    f.n = ((result & 0x80u) != 0u);
    f.c = carry;
}

Byte alu_add(Byte a, Byte b, Flags& f) {
    std::uint16_t value = static_cast<std::uint16_t>(a) + static_cast<std::uint16_t>(b);
    Byte result = static_cast<Byte>(value);
    update_flags(result, value > 0xFFu, f);
    return result;
}

Byte alu_sub(Byte a, Byte b, Flags& f) {
    std::uint16_t value = static_cast<std::uint16_t>(a) - static_cast<std::uint16_t>(b);
    Byte result = static_cast<Byte>(value);
    update_flags(result, a >= b, f);
    return result;
}

Byte alu_and(Byte a, Byte b, Flags& f) {
    Byte result = static_cast<Byte>(a & b);
    update_flags(result, false, f);
    return result;
}

Byte alu_or(Byte a, Byte b, Flags& f) {
    Byte result = static_cast<Byte>(a | b);
    update_flags(result, false, f);
    return result;
}

Byte alu_xor(Byte a, Byte b, Flags& f) {
    Byte result = static_cast<Byte>(a ^ b);
    update_flags(result, false, f);
    return result;
}

Byte alu_not(Byte a, Flags& f) {
    Byte result = static_cast<Byte>(~a);
    update_flags(result, false, f);
    return result;
}

Byte alu_shl(Byte a, Byte b, Flags& f) {
    (void)b;
    std::uint16_t value = static_cast<std::uint16_t>(a) << 1;
    Byte result = static_cast<Byte>(value);
    update_flags(result, (value & 0x100u) != 0u, f);
    return result;
}

Byte alu_shr(Byte a, Byte b, Flags& f) {
    (void)b;
    bool carry = (a & 0x01u) != 0u;
    Byte result = static_cast<Byte>(a >> 1);
    update_flags(result, carry, f);
    return result;
}

Byte alu_inc(Byte a, Flags& f) {
    std::uint16_t value = static_cast<std::uint16_t>(a) + 1u;
    Byte result = static_cast<Byte>(value);
    update_flags(result, a == 0xFFu, f);
    return result;
}

Byte alu_dec(Byte a, Flags& f) {
    std::uint16_t value = static_cast<std::uint16_t>(a) - 1u;
    Byte result = static_cast<Byte>(value);
    update_flags(result, a == 0u, f);
    return result;
}