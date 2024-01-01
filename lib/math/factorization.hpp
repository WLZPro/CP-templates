#pragma once

#include <numeric>
#include <vector>

#include "math/primes.hpp"
#include "math/mod_operations.hpp"

// https://cp-algorithms.com/algebra/factorization.html#implementation_1
// Assumptions: `1 <= n <= 7.2e18`, `n` is not prime
template<typename T>
constexpr T nontrivial_divisor(T n, const T &x0 = 2, T c = 1) {
    if (!(n & 1)) return 2;
    if constexpr (sizeof(T) > 4)  if (n <= (std::numeric_limits<uint32_t>::max() >> 2)) return nontrivial_divisor<uint32_t>(n);
    if constexpr (sizeof(T) <= 4) if (n >  (std::numeric_limits<uint32_t>::max() >> 2)) return nontrivial_divisor<uint64_t>(n);

    using uintx_t  = std::conditional_t<(sizeof(T) <= 4), uint32_t, uint64_t>;
    using uint2x_t = std::conditional_t<(sizeof(T) <= 4), uint64_t, __uint128_t>;

    const montgomery_multiplication<uintx_t, uint2x_t> mm(n);

    #define abs_diff(x, y) ((x) > (y) ? (x) - (y) : (y) - (x))

    for (; ; c++) {
        uintx_t x = mm.convert(x0), g = 1, q = mm.convert(1), xs, y;

        auto f_eq = [&mm, &n, &c](uintx_t &a) -> void {
            a = mm.reduce(mm.mul(a, a));
            if ((a += c) >= (static_cast<uintx_t>(n) << 1)) a -= n;
            a = mm.convert(a);
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
                    q = mm.mul(q, abs_diff(mm.val(x), mm.val(y)));
                }
                g = std::gcd(mm.val(q), n);
                k += m;
            }
            l <<= 1;
        }
        if (g == static_cast<uintx_t>(n)) {
            do {
                f_eq(xs);
                g = std::gcd(abs_diff(mm.val(xs), mm.val(y)), n);
            } while (g == 1);
        }
        if (g != 1 && g != static_cast<uintx_t>(n)) return g;
    }
}

template<typename T>
std::vector<T> factorize(T n) {
    if (n == 1) return std::vector<T>();
    std::vector<T> ans(1, n);
    for (int i = 0; i < static_cast<int>(ans.size()); i++) {
        while (!primes::is_prime(ans[i])) {
            T d = ans[i] <= static_cast<T>(primes::computed_up_to) ? primes::spf[ans[i]] : nontrivial_divisor(ans[i]);
            ans[i] /= d; ans.push_back(d);
        }
    }
    return ans;
}