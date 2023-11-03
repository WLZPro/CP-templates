#ifndef MATH_PRIMES_HPP
#define MATH_PRIMES_HPP 1

#include <vector>

namespace primes {

    int _sz = -1;
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
        if (_n <= _sz) return;
        _n = std::max(_n, 2);

        spf.resize(_n + 1);
        std::fill(spf.begin() + _sz + 1, spf.end(), 0);

        is_prime.resize(_n + 1); is_prime[0] = is_prime[1] = false;
        std::fill(is_prime.begin() + _sz + 1, is_prime.end(), false); 

        mu.resize(_n + 1); mu[1] = 1;
        phi.resize(_n + 1); phi[1] = 1;

        for (int i = std::max(2, _sz + 1); i <= _n; i++) {
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

        _sz = _n;
    }
};

#endif // MATH_PRIMES_HPP