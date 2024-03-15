#pragma once

#include "math/montgomery_multiplication.hpp"

#include <type_traits>

// Assumptions: `1 <= n <= 1e18`
template<typename T = uint64_t, std::enable_if_t<(std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>)>* = nullptr>
constexpr bool is_prime(T n) {
    constexpr uint32_t uint32_t_threshold = std::numeric_limits<uint32_t>::max() >> 2;
    if constexpr (sizeof(T) == 8) if (n <= uint32_t_threshold) return is_prime<uint32_t>(n);
    if constexpr (sizeof(T) == 4) {
        if (n > uint32_t_threshold) return is_prime<uint64_t>(n);
        if (n == 1) return false;
        if (n == 2 || n == 7 || n == 61) return true;
    }
    if (!(n & 1)) return false;

    using uintx_t  = T;
    #ifdef __SIZEOF_INT128__
    using uint2x_t = std::conditional_t<(sizeof(T) == 4), uint64_t, __uint128_t>;
    #else
    using uint2x_t = uint64_t;
    #endif
    
    const montgomery_multiplication<uintx_t, uint2x_t> mm(n);
    const uintx_t one = mm.convert(1), minus_one = mm.convert(n - 1);

    uintx_t d = n - 1;
    if constexpr (sizeof(T) == 4) d >>= __builtin_ctz(d);
    else                          d >>= __builtin_ctzll(d);

    auto check_sprp = [&](uintx_t a) -> bool {
        uintx_t t = d, y = mm.pow(mm.convert(a), d);
        while (t != static_cast<uintx_t>(n - 1) && !mm.equiv(y, one) && !mm.equiv(y, minus_one)) y = mm.mul(y, y), t <<= 1;
        if (!mm.equiv(y, minus_one) && !(t & 1)) return false;
        return true;
    };
        
    if constexpr (sizeof(T) == 4)
        for (uintx_t a : {2, 7, 61}) { if (!check_sprp(a)) return false; } 
    else                         
        for (uintx_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) { if (!check_sprp(a)) return false; }

    return true;
}

// Assumptions: `1 <= n <= 1e18`
template<typename T, std::enable_if_t<(!std::is_same_v<T, uint32_t> && !std::is_same_v<T, uint64_t>)>* = nullptr>
constexpr bool is_prime(T n) {
    if constexpr (sizeof(T) <= 4) return is_prime<uint32_t>(n);
    else                          return is_prime<uint64_t>(n);
}