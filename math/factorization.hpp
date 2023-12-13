#pragma once

#include <numeric>
#include <vector>

#include "math/primes.hpp"

// https://cp-algorithms.com/algebra/factorization.html#implementation_1
template<typename T>
T nontrivial_divisor(const T &n, const T &x0 = 2, T c = 1) {
    if (n <= primes::n) return primes::spf[n];
    if (primes::is_definitely_prime(n)) return n;

    for (; ; c++) {
        T x(x0), g(1), q(1), xs, y;

        auto f_eq = [&n, &c](T &a) -> void {
            a = ((__uint128_t) a * a) % n;
            if ((a += c) >= n) a -= n;
        };

        int m = 1 << 7, l = 1;
        while (g == 1) {
            y = x;
            for (int i = 0; i < l; i++) f_eq(x);
            int k = 0;
            while (k < l && g == 1) {
                xs = x;
                for (int i = 0; i < m && i < l - k; i++) {
                    f_eq(x);
                    q = ((__uint128_t) q * std::abs(y - x)) % n;
                }
                g = std::gcd(q, n);
                k += m;
            }
            l <<= 1;
        }
        if (g == n) {
            do {
                f_eq(xs);
                g = std::gcd(std::abs(xs - y), n);
            } while (g == 1);
        }
        if (g != 1 && g != n) return g;
    }
}

template<typename T>
std::vector<T> factorize(const T &n) {
    if (n == 1) return std::vector<T>();
    std::vector<T> ans(1, n);
    for (int i = 0; i < static_cast<int>(ans.size()); i++) {
        T d;
        while (true) {
            d = nontrivial_divisor(ans[i]);
            if (d == ans[i]) break;
            ans[i] /= d; ans.push_back(d);
        }
    }
    return ans;
}