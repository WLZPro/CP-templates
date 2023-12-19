// https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "dp/min_plus_convolution.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];

    vector<int> ans = convex_convex_min_plus_conv(a, b);
    for (int i = 0; i < n + m - 1; i++) cout << ans[i] << ' ';
    cout << '\n';

    return 0;
}