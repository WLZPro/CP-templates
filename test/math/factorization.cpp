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

    int t; cin >> t;
    while (t--) {
        unsigned long long n; cin >> n;
        vector<unsigned long long> ans = factorize(n);
        sort(ans.begin(), ans.end());
        cout << (int) ans.size();
        for (const unsigned long long &x : ans) cout << ' ' << x;
        cout << '\n';
    }

    return 0;
}   