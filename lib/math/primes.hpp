#pragma once

#include "math/montgomery_multiplication.hpp"

#include <vector>
#include <algorithm>
#include <random>

namespace primes {

    int computed_up_to = 0;
    std::vector<int> primes;
    std::vector<bool> is_prime_v = {false, false};

    // Smallest prime factor
    std::vector<int> spf;

    // Möbius function
    std::vector<int> mu;

    // Euler's totient function
    std::vector<int> phi;

    // https://cp-algorithms.com/algebra/prime-sieve-linear.html
    void sieve_up_to(int n) {
        if (n <= computed_up_to) return;
        computed_up_to = n;

        spf.assign(n + 1, 0);
        is_prime_v.assign(n + 1, true); is_prime_v[0] = is_prime_v[1] = false;
        mu.resize(n + 1); mu[1] = 1;
        phi.resize(n + 1); phi[1] = 1;

        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) spf[i] = i, primes.push_back(i);
            for (int j = 0; i * primes[j] <= n; j++) {
                spf[i * primes[j]] = primes[j];
                is_prime_v[i * primes[j]] = false;
                if (primes[j] == spf[i]) break;
            }

            if (spf[i] == spf[i / spf[i]]) {
                mu[i] = 0;
                phi[i] = phi[i / spf[i]] * spf[i];
            } else {
                mu[i] = -mu[i / spf[i]];
                phi[i] = phi[i / spf[i]] * (spf[i] - 1);
            }
        }
    }
    
    // Assumptions: `1 <= n <= 1e18`
    template<typename T>
    constexpr bool is_prime_constexpr(T n) {
        if constexpr (sizeof(T) > 4) if (n <= (std::numeric_limits<uint32_t>::max() >> 2)) return is_prime_constexpr<uint32_t>(n);
        if constexpr (sizeof(T) <= 4) {
            if (n > (std::numeric_limits<uint32_t>::max() >> 2)) return is_prime_constexpr<uint64_t>(n);
            if (n == 1) return false;
            if (n == 2 || n == 7 || n == 61) return true;
        }
        if (!(n & 1)) return false;

        using uintx_t = std::conditional_t<(sizeof(T) <= 4), uint32_t, uint64_t>;
        using uint2x_t = std::conditional_t<(sizeof(T) <= 4), uint64_t, __uint128_t>;
        
        auto mm = montgomery_multiplication<uintx_t, uint2x_t>(n);
        const uintx_t one = mm.convert(1), minus_one = mm.convert(n - 1);
        uintx_t d = n - 1;
        while (!(d & 1)) d >>= 1;

        #define LOOP uintx_t t = d, y = mm.pow(mm.convert(a), d); \
                     while (t != n - 1 && !mm.equiv(y, one) && !mm.equiv(y, minus_one)) y = mm.mul(y, y), t <<= 1; \
                     if (!mm.equiv(y, minus_one) && !(t & 1)) return false
        
        if constexpr (sizeof(T) <= 4) for (uintx_t a : {2, 7, 61}) { LOOP; }
        else                          for (uintx_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) { LOOP; }

        #undef LOOP

        return true;
    }
    template<uint64_t n> constexpr bool is_prime_64_bit_v = is_prime_constexpr(n);

    template<typename T>
    bool is_prime(T n) {
        if (n <= static_cast<T>(computed_up_to)) return is_prime_v[n];
        return is_prime_constexpr(n);
    }
};