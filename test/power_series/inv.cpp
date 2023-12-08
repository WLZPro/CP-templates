// https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "math/modint.hpp"
#include "polynomial/power_series.hpp"
#include "util/fast_io.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    int n; cin >> n;
    poly<mint> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i].set(x, true);
    }

    a = inv(a);
    for (auto &x : a) cout << x.val() << ' ';
    cout << '\n';

    return 0;
}