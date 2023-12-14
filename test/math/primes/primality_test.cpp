// https://judge.yosupo.jp/problem/primality_test
#include <bits/stdc++.h>
using namespace std;

#include "util/fast_io.hpp"
#include "math/primes.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    primes::sieve_up_to((int) 1e6);

    int t; cin >> t;
    while (t--) {
        long long n; cin >> n;
        if (primes::is_prime(n)) cout << 'Y' << 'e' << 's' << '\n';
        else cout << 'N' << 'o' << '\n';
    }
    return 0;
}