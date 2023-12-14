#ifndef MATH_INT128_HPP
#define MATH_INT128_HPP 1

#include <iostream>

std::ostream &operator<<(std::ostream &out, const __int128_t &_x) {
    __int128_t x = _x;
    if (x < 0) out << '-', x = -x;
    if (x >= 10) out << (x / 10);
    out << (char) (x % 10 + '0');
    return out;
}

#endif // MATH_INT128_HPP