#pragma once

#include "math/montgomery_multiplication.hpp"
#include "math/miller_rabin.hpp"

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
    
    template<typename T>
    bool is_prime(T n) {
        if (n <= static_cast<T>(computed_up_to)) return is_prime_v[n];
        return is_prime_constexpr(n);
    }
};