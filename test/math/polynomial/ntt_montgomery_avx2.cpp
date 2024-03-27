// https://judge.yosupo.jp/problem/convolution_mod
#include <bits/stdc++.h>
using namespace std;

#ifndef DEBUG
#define debug(...)
#else
#include "debug.hpp"
#endif

#include "external/fast_io_nor.hpp"
#include "math/montgomery_32_avx2.hpp"
#include "math/polynomial/ntt_montgomery_avx2.hpp"

constexpr uint32_t md = 998244353;
constexpr int N = 1 << 23;

uint32_t a[N], b[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;

    int k = __lg(max(8, n + m - 2)) + 1;

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    ntt_avx2::conv_via_montgomery<md>(a, b, k);

    for (int i = 0; i < n + m - 1; ++i) cout << a[i] << ' ';
    cout << '\n';

    return 0;
}