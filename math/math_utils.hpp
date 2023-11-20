#ifndef MATH_MATH_UTILS_HPP
#define MATH_MATH_UTILS_HPP 1

#include <tuple>
#include <utility>

// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#iterative-version
template<typename T1, typename T2>
T1 extgcd(const T1& a, const T1& b, T2 &x, T2 &y) {
    x = 1; y = 0;
    T1 a1(a), b1(b);
    T2 x1 = 0, y1 = 1;
    while (b1 != 0) {
        T1 q = a1 / b1;
        std::tie(x, x1) = std::make_pair(x1, x - q * x1);
        std::tie(y, y1) = std::make_pair(y1, y - q * y1);
        std::tie(a1, b1) = std::make_pair(b1, a1 - q * b1);
    }
    return a1;
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

#endif // MATH_MATH_UTILS_HPP