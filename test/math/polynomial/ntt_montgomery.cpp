// https://judge.yosupo.jp/problem/convolution_mod
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "external/fast_io_nor.hpp"
#include "math/polynomial/ntt_montgomery.hpp"

constexpr uint32_t md = 998244353;
constexpr int N = 1 << 20;

uint32_t a[N], b[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;

    int k = __lg(max(1, n + m - 2)) + 1;

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    ntt::conv_via_montgomery<md>(a, b, k);

    for (int i = 0; i < n + m - 1; ++i) cout << a[i] << ' ';
    cout << '\n';

    return 0;
}