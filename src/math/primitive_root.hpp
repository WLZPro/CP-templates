#pragma once

#include "math/montgomery_multiplication.hpp"
#include "math/factorization.hpp"

#include <type_traits>
#include <limits>

// Assumptions: `p` is prime
template<typename T, std::enable_if_t<(std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>)>* = nullptr>
constexpr T primitive_root_prime(T p) {
    if (p == 2) return 1;
    if (p == 167772161) return 3;
    if (p == 469762049) return 3;
    if (p == 754974721) return 11;
    if (p == 998244353) return 3;

    constexpr uint32_t uint32_t_threshold = std::numeric_limits<uint32_t>::max() >> 2;
    if constexpr (sizeof(T) == 8) if (p <= uint32_t_threshold) return primitive_root_prime<uint32_t>(p);
    if constexpr (sizeof(T) == 4) if (p >  uint32_t_threshold) return primitive_root_prime<uint64_t>(p);

    using uintx_t  = T;
    using uint2x_t = std::conditional_t<(sizeof(T) == 4), uint64_t, __uint128_t>;

    uintx_t n = (p - 1) >> __builtin_ctzll(p - 1), check[20]; check[0] = p >> 1;
    int k = 1;
    while (n > 1) {
        uintx_t d = n;
        while (!is_prime(d)) d = nontrivial_divisor(d);
        check[k++] = (p - 1) / d;
        while (!(n % d)) n /= d;
    }

    const montgomery_multiplication<uintx_t, uint2x_t> mm(p);
    const uintx_t one = mm.convert(1);
    for (uintx_t g = 2; ; g++) {
        bool root = true;
        uintx_t mg = mm.convert(g);
        for (int i = 0; i < k; i++) 
            if (mm.equiv(one, mm.pow(mg, check[i]))) {
                root = false; break;
            }
        if (root) return g;
    }
    __builtin_unreachable();
}

// Assumptions: `p >= 0`, `p` is prime
template<typename T, std::enable_if_t<(!std::is_same_v<T, uint32_t> && !std::is_same_v<T, uint64_t>)>* = nullptr>
constexpr T primitive_root_prime(T p) {
    if constexpr (std::numeric_limits<T>::digits <= 32) return primitive_root_prime<uint32_t>(p);
    else                                                return primitive_root_prime<uint64_t>(p);
}