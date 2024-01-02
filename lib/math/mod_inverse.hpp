#pragma once

#include "math/mod_operations.hpp"
#include "math/miller_rabin.hpp"

// Assumptions: `0 <= a < md`
template<typename T>
constexpr T inv_mod_prime(const T &a, const T &md) {
    if (a <= 1) return a;
    return md - mul_mod(md / a, inv_mod_prime(md % a, md), md);
}

// Assumptions: `0 <= a < md`
template<typename T>
constexpr T inv_mod(const T &a, const T &md) {
    T x, y; extgcd_mod(a, md, x, y, md);
    return x;
}

// Assumptions: `0 <= a < md`
template<typename T, T md>
constexpr T inv_mod(const T &a) {
    if constexpr (is_prime(md)) return inv_mod_prime(a, md);
    return inv_mod(a, md);
}