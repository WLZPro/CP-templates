#ifndef MATH_PRIMES_HPP
#define MATH_PRIMES_HPP 1

#include <bits/stdc++.h>
using namespace std;

/**
 * pf: largest prime factor
 * phi: Euler phi function
 * mu: Mobius function
 */
vector<int> pf, phi, mu;
vector<int> primes;

void gen_primes(int n) {
    pf.assign(n + 1, -1);
    phi.resize(n + 1);
    mu.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) phi[i] = i;
    pf[0] = pf[1] = -1;
    for (int i = 2; i <= (int) n; i++) {
        if (pf[i] != -1) continue;
        primes.push_back(i);
        for (int j = i; j <= n; j += i) {
            pf[j] = i;
            phi[j] -= phi[j] / i;
            mu[j] = -mu[j / i];
        }
        if (i <= n / i) for (int j = i * i; j <= n; j += i * i) mu[j] = 0;
    }
}

#endif // MATH_PRIMES_HPP