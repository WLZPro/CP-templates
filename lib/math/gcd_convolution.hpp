#pragma once

#include <vector>

#include "math/primes.hpp"

// https://codeforces.com/blog/entry/112346?#comment-1001131
template<typename T>
std::vector<T> gcd_conv(std::vector<T> a, std::vector<T> b) {
    int n = static_cast<int>(a.size()) - 1;
    primes::sieve(n << 1);

    for (int i = 0; primes::primes[i] <= n; i++) {
        int p = primes::primes[i];
        for (int j = n / p; j >= 1; j--) a[j] += a[j * p], b[j] += b[j * p];
    }

    for (int i = 1; i <= n; i++) a[i] *= b[i];

    for (int i = 0; primes::primes[i] <= n; i++) 
        for (int j = 1; j * primes::primes[i] <= n; j++) 
            a[j] -= a[j * primes::primes[i]];

    return a;
}