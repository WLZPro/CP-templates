// https://www.spoj.com/problems/PON/
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "math/primes.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    primes::sieve((int) 1e6);

    int t; cin >> t;
    while (t--) {
        long long x; cin >> x;
        if (primes::is_definitely_prime(x)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}