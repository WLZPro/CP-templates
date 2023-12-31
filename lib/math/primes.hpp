#pragma once

#include "math/mod_operations.hpp"

#include <vector>
#include <algorithm>
#include <random>

namespace primes {

    int computed_up_to = -1;
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

    // https://github.com/atcoder/ac-library/blob/master/atcoder/internal_math.hpp
    // Assumptions: `1 <= n <= UINT_MAX`
    template<typename T>
    constexpr bool is_prime_32_bit(const T &n) {
        if (n <= 1) return false;
        if (n == 2 || n == 7 || n == 61) return true;
        if (!(n & 1)) return false;
        T d = (n - 1);
        while (!(d & 1)) d >>= 1;
        constexpr T bases[] = {2, 7, 61};
        for (const T &a : bases) {
            T t = d, y = pow_mod(a, t, n);
            while (t != n - 1 && y != 1 && y != n - 1) y = mul_mod(y, y, n), t <<= 1;
            if (y != n - 1 && !(t & 1)) return false;
        }
        return true;
    }

    // https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h
    // Assumptions: `1 <= n <= 7.2e18`, `is_prime_32_bit` fails on `n`
    template<typename T>
    constexpr bool is_prime_64_bit(T n) {
        int s = __builtin_ctzll(n - 1); T d = n >> s;

        constexpr T bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        for (const T &a : bases) {
            T p = pow_mod(a, d, n); int i = s;
            while (p != 1 && p != n - 1 && i--) p = mul_mod(p, p, n);
            if (p != n - 1 && i != s) return false;
        }
        return true;
    }
    template<uint32_t n> constexpr bool is_prime_32_bit_v = is_prime_32_bit(n);

    template<typename T>
    constexpr bool is_prime_constexpr(const T &n) {
        if constexpr (sizeof(T) <= 4) return is_prime_32_bit(n);
        else {
            if (n <= std::numeric_limits<uint32_t>::max()) return is_prime_32_bit(n);
            else return is_prime_64_bit(n);
        }
    }
    template<uint64_t n> constexpr bool is_prime_64_bit_v = is_prime_constexpr(n);

    template<typename T>
    bool is_prime(const T &n) {
        if (n <= computed_up_to) return is_prime_v[n];
        return is_prime_constexpr(n);
    }
};