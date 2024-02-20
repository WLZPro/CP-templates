#pragma once

#include "util/type_traits.hpp"
#include "math/mod_operations.hpp"
#include "math/mod_inverse.hpp"

template<int id>
class dynamic_modint {
    using mint = dynamic_modint;

    public:
    static inline uint32_t md;

    static uint32_t mod() { return md; }

    constexpr static void set_mod(uint32_t mod) { md = mod; }

    constexpr dynamic_modint() : x(0) {}

    template<typename T>
    constexpr dynamic_modint(const T &_x, bool raw = false) : x() { set(_x, raw); }

    template<typename T>
    constexpr mint &operator=(const T &_x) { set(_x); return *this; }

    template<typename T>
    constexpr void set(const T &_x, bool raw = false) {
        if (raw || (0 <= _x && static_cast< make_unsigned_better_t<T> >(_x) < md)) x = _x;
        else {
            int32_t tmp = _x % static_cast<int32_t>(md);
            if (tmp < 0) tmp += md;
            x = static_cast<uint32_t>(tmp);
        }
    }

    constexpr int val() const { return static_cast<int>(x); }

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

    mint inv() const { return inv(x); }
    constexpr mint inv_constexpr() const { return inv_constexpr(x); }

    static mint inv(int n) {
        return mint(inv_mod<uint32_t>(n, md), true);
    }

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
    uint32_t x;
};