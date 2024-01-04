// https://judge.yosupo.jp/problem/primitive_root
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "math/primitive_root.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int q; cin >> q;
    while (q--) {
        long long p; cin >> p;
        cout << primitive_root_prime(p) << '\n';
    }

    return 0;
}