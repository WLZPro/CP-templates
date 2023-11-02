#ifndef MATH_MODINT_HPP
#define MATH_MODINT_HPP 1

#include "math/math_utils.hpp"

#include <algorithm>
#include <iostream>
#include <string>

template<const int MOD>
class modint {
    private: int x;

    public:
    
    // Assignment/constuctors
    modint() : x(0) {}

    template<typename T>
    void set(const T _x, bool raw = false) {
        if (raw || (0 <= _x && _x < MOD)) x = _x;
        else {
            x = _x % MOD;
            if (x < 0) x += MOD;
        }
    }

    template<typename T>
    modint(const T &_x, bool raw = false) { set(_x, raw); }

    template<typename T>
    constexpr modint &operator=(const T &_x) { set(_x); return *this; }

    // Binary arithmetic operators
    constexpr modint &operator+=(const modint &rhs) { x += rhs.x; if (x >= MOD) x -= MOD; return *this; }
    constexpr friend modint operator+(modint lhs, const modint &rhs) { return lhs += rhs; }

    constexpr modint &operator-=(const modint &rhs) { x -= rhs.x; if (x < 0) x += MOD; return *this; }
    constexpr friend modint operator-(modint lhs, const modint &rhs) { return lhs -= rhs; }

    constexpr modint &operator*=(const modint &rhs) { x = (unsigned long long) x * rhs.x % MOD; return *this; }
    constexpr friend modint operator*(modint lhs, const modint &rhs) { return lhs *= rhs; }

    constexpr modint inv() const { modint x1, y1; extgcd(x, MOD, x1, y1); return x1; }

    constexpr modint &operator/=(const modint &rhs) { operator*=(rhs.inv()); return *this; }
    constexpr friend modint operator/(modint lhs, const modint &rhs) { return lhs /= rhs; }

    constexpr modint &operator%=(const modint &rhs) { x %= rhs.val(); return *this; }
    constexpr friend modint operator%(modint lhs, const modint &rhs) { return lhs %= rhs; }

    // Unary arithemtic operators
    constexpr modint operator-() const { return modint(MOD - x, true); }
    constexpr modint operator+() const { return modint(*this); }

    // Increment/decrement
    constexpr modint &operator++() { if (++x == MOD) x = 0; return *this; }
    constexpr modint operator++(int) { modint cpy(*this); operator++(); return cpy; }

    constexpr modint &operator--() { if (--x < 0) x = MOD - 1; return *this; }
    constexpr modint operator--(int) { modint cpy(*this); operator--(); return cpy; }

    // Comparison operators
#if __cplusplus < 202002L
    constexpr friend bool operator==(const modint &lhs, const modint &rhs) { return lhs.val() == rhs.val(); }
    constexpr friend bool operator!=(const modint &lhs, const modint &rhs) { return !(lhs == rhs); }
    constexpr friend bool operator< (const modint &lhs, const modint &rhs) { return lhs.val() < rhs.val(); }
    constexpr friend bool operator> (const modint &lhs, const modint &rhs) { return rhs < lhs; }
    constexpr friend bool operator<=(const modint &lhs, const modint &rhs) { return !(lhs > rhs); }
    constexpr friend bool operator>=(const modint &lhs, const modint &rhs) { return !(lhs < rhs); }
#else
    constexpr auto operator<=>(const modint&) const = default;
#endif

    // Input/output
    friend std::istream &operator>>(std::istream &is, modint &m) { is >> m.x; return is; }
    friend std::ostream &operator<<(std::ostream &os, const modint &m) { os << m.x; return os; }

    // Casting
    template<typename T>
    constexpr operator T() const { return x; }

    // Value extraction
    constexpr int val() const { return x; }

    // Debugging
    inline friend std::string to_string(const modint &m) {
        using namespace std;
        return to_string(m.x);
    }
};

template<const int MOD, typename T, typename S>
modint<MOD> mpow(const T &a, const S &b) { return bpow(modint<MOD>(a), b); }

using modint1000000007 = modint<1000000007>;
using modint998244353 = modint<998244353>;

#endif // MATH_MODINT_HPP
