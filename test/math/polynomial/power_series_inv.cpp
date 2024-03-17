// https://judge.yosupo.jp/problem/inv_of_formal_power_series
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "external/fast_io_nor.hpp"
#include "math/polynomial/power_series_inv.hpp"

constexpr uint32_t md = 998244353;
constexpr int N = 1 << 21;

uint32_t a[N], b[N], c[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    int k = __lg(n - 1) + 1;
    inv_via_montgomery<md>(a, b, c, k);

    for (int i = 0; i < n; i++) cout << b[i] << ' ';
    cout << '\n';

    return 0;
}