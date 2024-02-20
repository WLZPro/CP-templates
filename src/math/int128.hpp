#pragma once

#include <iostream>

template<typename T, std::enable_if_t< std::is_same_v<T, __int128_t> || std::is_same_v<T, __uint128_t> >* = nullptr>
std::ostream &operator<<(std::ostream &out, T x) {
    if (x < 0) out << '-', x = -x;
    if (x >= 10) out << (x / 10);
    out << (char) (x % 10 + '0');
    return out;
}

template<typename T, std::enable_if_t< std::is_same_v<T, __int128_t> || std::is_same_v<T, __uint128_t> >* = nullptr>
std::istream &operator>>(std::istream &in, T &x) {
    std::string s; in >> s;
    x = 0; bool sgn = true;
    for (auto &c : s) {
        if (isdigit(c)) x = x * 10 + (c - '0');
        else sgn = !sgn;
    }
    if (!sgn) x = -x;
    return in;
}