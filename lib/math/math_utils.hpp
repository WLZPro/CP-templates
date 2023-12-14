#pragma once

template<typename T, typename TExp>
constexpr T bpow(T a, TExp b) {
    T ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}