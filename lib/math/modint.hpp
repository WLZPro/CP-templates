#pragma once

#include <string>

#include "math/mod_operations.hpp"
#include "math/mod_inverse.hpp"

template<unsigned int md>
class modint {
    using mint = modint;

    public:
    static constexpr unsigned int mod = md;

    constexpr modint() : x(0) {}

    template<typename T>
    constexpr modint(const T &_x, bool raw = false) { set(_x, raw); }

    template<typename T>
    constexpr mint &operator=(const T &_x) { set(_x); return *this; }

    template<typename T>
    constexpr void set(const T &_x, bool raw = false) {
        if (raw || (0 <= _x && static_cast<unsigned int>(_x) < md)) x = _x;
        else {
            long long tmp = _x % md;
            if (tmp < 0) tmp += md;
            x = (unsigned int) tmp;
        }
    }

    constexpr unsigned int val() const { return x; }

    template<typename T>
    constexpr operator T() const { return (T) x; }

    constexpr mint &operator++() {
        if (++x == md) x = 0;
        return *this;
    }

    constexpr mint operator++(int) {
        mint cpy(*this); operator++();
        return cpy;
    }

    constexpr mint &operator--() {
        if (x == 0) x = md;
        x--;
        return *this;
    }

    constexpr mint operator--(int) {
        mint cpy(*this); operator--();
        return cpy;
    }

    constexpr mint &operator+=(const mint &rhs) {
        if ((x += rhs.x) >= md) x -= md;
        return *this;
    }
    constexpr friend mint operator+(mint lhs, const mint &rhs) { return lhs += rhs; }

    constexpr mint &operator-=(const mint &rhs) {
        if ((x -= rhs.x) >= md) x += md;
        return *this;
    }
    constexpr friend mint operator-(mint lhs, const mint &rhs) { return lhs -= rhs; }

    constexpr mint &operator*=(const mint &rhs) {
        x = mul_mod(x, rhs.x, md);
        return *this;
    }
    constexpr friend mint operator*(mint lhs, const mint &rhs) { return lhs *= rhs; }

    constexpr mint &operator/=(const mint &rhs) {
        operator*=(rhs.inv());
        return *this;
    }

    constexpr friend mint operator/(mint lhs, const mint &rhs) { return lhs /= rhs; }

    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return mint(md - x, true); }

    constexpr mint inv() const { return invs_mod<md>::get(x); }

    constexpr friend bool operator==(const mint &a, const mint &b) { return a.x == b.x; }
    constexpr friend bool operator!=(const mint &a, const mint &b) { return a.x != b.x; }
    constexpr friend bool operator< (const mint &a, const mint &b) { return a.x <  b.x; }
    constexpr friend bool operator> (const mint &a, const mint &b) { return a.x >  b.x; }
    constexpr friend bool operator<=(const mint &a, const mint &b) { return a.x <= b.x; }
    constexpr friend bool operator>=(const mint &a, const mint &b) { return a.x >= b.x; }

    template<typename InputStream>
    friend InputStream  &operator>>(InputStream  &is, mint &m) { return is >> m.x; }
    template<typename OutputStream>
    friend OutputStream &operator<<(OutputStream &os, const mint &m) { return os << m.x; }

    inline friend std::string to_string(const mint &m) { return std::to_string(m.x); }

    private:
    unsigned int x;
};

using modint1000000007 = modint<1000000007>;
using modint998244353  = modint<998244353>;