#pragma once

#include "math/mod_operations.hpp"
#include "math/montgomery_multiplication.hpp"

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

    #define equiv(x, y, n) (((x) >= (n) ? (x) - (n) : (x)) == ((y) >= (n) ? (y) - (n) : (y)))

    // https://github.com/atcoder/ac-library/blob/master/atcoder/internal_math.hpp
    // Assumptions: `1 <= n <= UINT_MAX`
    constexpr bool is_prime_32_bit(uint32_t n) {
        if (n <= 1) return false;
        if (n == 2 || n == 7 || n == 61) return true;
        if (!(n & 1)) return false;

        montgomery_multiplication_32 &mm = global_montgomery_multiplication_32<-1>;
        mm.set_mod(n);
        uint32_t d = n - 1;
        while (!(d & 1)) d >>= 1;
        constexpr uint32_t bases[] = {2, 7, 61};
        const uint32_t one = mm.convert(1), minus_one = mm.convert(n - 1);
        for (uint32_t a : bases) {
            uint32_t t = d, y = mm.pow(mm.convert(a), d);
            while (t != n - 1 && !equiv(y, one, n) && !equiv(y, minus_one, n)) y = mm.mul(y, y), t <<= 1;
            if (!equiv(y, minus_one, n) && !(t & 1)) return false;
        }
        return true;
    }
    template<uint32_t n> constexpr bool is_prime_32_bit_v = is_prime_32_bit(n);

    // https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h
    // Assumptions: `UINT_MAX < n <= 7.2e18`
    constexpr bool is_prime_64_bit(uint64_t n) {
        if (!(n & 1)) return false;

        montgomery_multiplication_64 &mm = global_montgomery_multiplication_64<-1>;
        mm.set_mod(n);
        uint64_t d = n - 1;
        while (!(d & 1)) d >>= 1;
        constexpr uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        const uint64_t one = mm.convert(1), minus_one = mm.convert(n - 1);
        for (uint64_t a : bases) {
            uint64_t t = d, y = mm.pow(mm.convert(a), d);
            while (t != n - 1 && !equiv(y, one, n) && !equiv(y, minus_one, n)) y = mm.mul(y, y), t <<= 1;
            if (!equiv(y, minus_one, n) && !(t & 1)) return false;
        }
        return true;
    }
    
    #undef equiv

    template<typename T>
    constexpr bool is_prime_constexpr(T n) {
        if constexpr (sizeof(T) <= 4) return is_prime_32_bit(n);
        else {
            if (n <= std::numeric_limits<uint32_t>::max()) return is_prime_32_bit(n);
            else return is_prime_64_bit(n);
        }
    }
    template<uint64_t n> constexpr bool is_prime_64_bit_v = is_prime_constexpr(n);

    template<typename T>
    bool is_prime(T n) {
        if (n <= computed_up_to) return is_prime_v[n];
        return is_prime_constexpr(n);
    }
};