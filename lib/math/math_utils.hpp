#pragma once

#include <utility>
#include <vector>

template<typename T>
constexpr T mod_inv(const T &a, const T &mod) {
    if (a <= 1) return a;
    return mod - (unsigned long long) (mod / a) * mod_inv(mod % a, mod) % mod;
}

// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#iterative-version
template<typename T1, typename T2>
constexpr T1 extgcd(T1 a, T1 b, T2 &x, T2 &y) {
    x = 1; y = 0;
    T2 x1(0), y1(1);
    while (b != 0) {
        T1 q = a / b;
        x = std::exchange(x1, x - q * x1);
        y = std::exchange(y1, y - q * y1);
        a = std::exchange(b, a - q * b);
    }
    return a;
}

template<typename T, typename TExp>
T bpow(T a, TExp b) {
    T ans = 1;
    while (b > 0) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

template<typename T, typename TExp>
constexpr T mod_pow(T a, TExp b, const T &md) {
    T ans = 1;
    while (b) {
        if (b & 1) ans = ((__uint128_t) ans * a) % md;
        a = ((__uint128_t) a * a) % md;
        b >>= 1;
    }
    return ans;
}

// https://codeforces.com/blog/entry/97562?#comment-864528
template<typename T>
T linear_floor_sum(const T &n, const T &m, const T &a, const T &b) {
    if (n <= 8) {
        T ans{0};
        for (int i = 0; i < n; i++) ans += (a * i + b) / m;
        return ans;
    }
    if (a >= m) return (a / m) * n * (n - 1) / 2 + linear_floor_sum(n, m, a % m, b);
    if (b >= m) return (b / m) * n + linear_floor_sum(n, m, a, b % m);
    T tmp = (a * (n - 1) + b) / m;
    return (n - 1) * tmp - linear_floor_sum(tmp, a, m, m - b - 1);
}