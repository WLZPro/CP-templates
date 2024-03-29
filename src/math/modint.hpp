#pragma once

#include <string>

#include "util/type_traits.hpp"
#include "math/mod_operations.hpp"
#include "math/mod_inverse.hpp"
#include "math/miller_rabin.hpp"

template<uint32_t md>
class modint {
    using mint = modint;

    public:
    static constexpr uint32_t mod = md;

    constexpr modint() : x(0) {}

    template<typename T>
    constexpr modint(const T &_x, bool raw = false) : x() { set(_x, raw); }

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
        x = mul(x, rhs.x);
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

    static inline int invs_up_to = 1, fact_up_to = 1;

    static void compute_inverses(int n) {
        if (n <= invs_up_to) return;
        _inv.resize(n + 1);
        if constexpr (is_prime(md))
            for (uint32_t a = invs_up_to + 1; a <= static_cast<uint32_t>(n); a++) _inv[a] = md - mul(md / a, _inv[md % a]);
        else 
            for (uint32_t a = invs_up_to + 1; a <= static_cast<uint32_t>(n); a++) _inv[a] = inv_constexpr(a);
        invs_up_to = n;
    }

    static void compute_factorials(int n) {
        if (n <= fact_up_to) return;
        compute_inverses(n);
        _fact.resize(n + 1); _inv_fact.resize(n + 1);
        for (uint32_t a = fact_up_to + 1; a <= static_cast<uint32_t>(n); a++) {
            _fact[a] = mul(_fact[a - 1], a);
            _inv_fact[a] = mul(_inv_fact[a - 1], _inv[a]);
        }
        fact_up_to = n;
    }

    static constexpr mint inv_constexpr(int n) {
        return mint(inv_mod<uint32_t, md>(static_cast<uint32_t>(n)), true);
    }

    static mint inv(int n) {
        if (n <= invs_up_to) return mint(_inv[n], true);
        return inv_constexpr(n);
    }
    static mint fact(int n) {
        if (n > fact_up_to) compute_factorials(n);
        return mint(_fact[n], true);
    }
    static mint inv_fact(int n) {
        if (n > fact_up_to) compute_factorials(n);
        return mint(_inv_fact[n], true);
    }

    static mint binom(int n, int k) {
        if (k < 0 || k > n) return mint(0, true);
        return fact(n) * inv_fact(k) * inv_fact(n - k);
    }

    static mint catalan(int n) { return binom(2 * n, n) * inv(n + 1); }

    private:
    uint32_t x;

    static inline std::vector<uint32_t> _inv = {0, 1}, _fact = {1, 1}, _inv_fact = {1, 1};

    static constexpr uint32_t mul(uint32_t a, uint32_t b) {
#if __cplusplus >= 202002L
        if (std::is_constant_evaluated()) return uint64_t(a) * b % md;
        else return mul_asm(a, b);
#else
        return uint64_t(a) * b % md;
#endif
    }

    // https://codeforces.com/blog/entry/73451
    static uint32_t mul_asm(uint32_t a, uint32_t b) {
        uint64_t x = uint64_t(a) * b;
        uint32_t xh = x >> 32, x1 = x, d, m;
        asm(
            "divl %4; \n\t"
            : "=a" (d), "=d" (m)
            : "d" (xh), "a" (x1), "r" (md)
        );
        return m;
    }
};

using modint1000000007 = modint<1000000007>;
using modint998244353  = modint<998244353>;