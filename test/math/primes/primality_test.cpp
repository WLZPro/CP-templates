// https://judge.yosupo.jp/problem/primality_test
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "math/primes.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        long long n; cin >> n;
        if (primes::is_prime_constexpr(n)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}