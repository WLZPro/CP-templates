#pragma once

#include <cstdint>
#include <limits>
#include <utility>

// Assumptions: `0 <= a, b < md`
template<typename T>
constexpr T add_mod(T a, T b, T md) {
    if (a + b >= md) return a + b - md;
    return a + b;
}

// Assumptions: `0 <= a, b < md`
template<typename T>
constexpr T sub_mod(T a, T b, T md) {
    if (a < b) return a - b + md;
    return a - b;
}

// Assumptions: `0 <= a, b < md`
template<typename T>
constexpr T mul_mod(T a, T b, T md) {
    if constexpr (sizeof(T) <= 4) return (static_cast<uint64_t>(a) * b) % md;
    else {
        if (a <= std::numeric_limits<uint32_t>::max() && b <= std::numeric_limits<uint32_t>::max())
            return (static_cast<uint64_t>(a) * b) % md;
        return (static_cast<__uint128_t>(a) * b) % md;
    }
}

template<typename T, typename TExp>
constexpr T pow_mod(T a, TExp b, const T &md) {
    T ans = 1;
    while (b) {
        if (b & 1) ans = mul_mod(ans, a, md);
        a = mul_mod(a, a, md);
        b >>= 1;
    }
    return ans;
}

// Assumptions: `0 <= a, b < md`
template<typename T>
constexpr T extgcd_mod(T a, T b, T &x, T &y, const T &md) {
    x = 1; y = 0;
    T x1(0), y1(1);
    while (b) {
        T q = a / b;
        x = std::exchange(x1, sub_mod(x, mul_mod(q, x1, md), md));
        y = std::exchange(y1, sub_mod(y, mul_mod(q, y1, md), md));
        a = std::exchange(b, a - q * b);
    }
    return a;
}