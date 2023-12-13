#pragma once

#include "math/math_utils.hpp"

#include <vector>
#include <algorithm>
#include <random>

namespace primes {

    int n = -1;
    std::vector<int> primes;
    std::vector<bool> is_prime;

    // Smallest prime factor
    std::vector<int> spf;

    // Möbius function
    std::vector<int> mu;

    // Euler's totient function
    std::vector<int> phi;

    // https://cp-algorithms.com/algebra/prime-sieve-linear.html
    void sieve(int _n) {
        if (_n <= n) return;
        _n = std::max(_n, 2);

        spf.resize(_n + 1);
        std::fill(spf.begin() + n + 1, spf.end(), 0);

        is_prime.resize(_n + 1); is_prime[0] = is_prime[1] = false;
        std::fill(is_prime.begin() + n + 1, is_prime.end(), true); 

        mu.resize(_n + 1); mu[1] = 1;
        phi.resize(_n + 1); phi[1] = 1;

        for (int i = 2; i <= _n; i++) {
            if (spf[i] == 0) spf[i] = i, primes.push_back(i);
            for (int j = 0; i * primes[j] <= _n; j++) {
                spf[i * primes[j]] = primes[j];
                is_prime[i * primes[j]] = false;
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

        n = _n;
    }

    // https://cp-algorithms.com/algebra/primality_tests.html#miller-rabin-primality-test
    template<typename T>
    bool __check_composite(T x, T a, T d, int s) {
        T y = mod_pow(a, d, x);
        if (y == 1 || y == x - 1) return false;
        for (int r = 1; r < s; r++) if ((y = ((__uint128_t) y * y) % x) == x - 1) return false;
        return true;
    } 

    // https://cp-algorithms.com/algebra/primality_tests.html#miller-rabin-primality-test
    template<typename T, int seed = -1>
    bool is_probably_prime(const T &x, int k = 5) {
        if (x <= n) return is_prime[x];
        static std::mt19937_64 rng(seed == -1 ? std::chrono::steady_clock().now().time_since_epoch().count() : seed);
        int s = 0; T d = x - 1;
        while (!(d & 1)) d >>= 1, s++;

        for (int i = 0; i < k; i++) {
            if (__check_composite(x, std::uniform_int_distribution<T>(static_cast<T>(2), x - 2)(rng), d, s)) return false;
        }
        return true;
    }

    // https://cp-algorithms.com/algebra/primality_tests.html#miller-rabin-primality-test
    template<typename T>
    bool is_definitely_prime(const T &x) {
        if (x <= n) return is_prime[x];
        int s = 0; T d = x - 1;
        while (!(d & 1)) d >>= 1, s++;

        for (T a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (x == a) return true;
            if (__check_composite(x, a, d, s)) return false;
            if (a == 7 && x <= std::numeric_limits<unsigned int>::max()) return true;
        }
        return true;
    }
};