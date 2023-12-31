// https://judge.yosupo.jp/problem/factorize
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "math/primes.hpp"
#include "math/factorization.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    primes::sieve_up_to((int) 1e6);

    int t; cin >> t;
    while (t--) {
        long long n; cin >> n;
        vector<long long> ans = factorize(n);
        sort(ans.begin(), ans.end());
        cout << (int) ans.size();
        for (const long long &x : ans) cout << ' ' << x;
        cout << '\n';
    }

    return 0;
}   