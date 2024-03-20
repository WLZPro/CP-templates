// https://judge.yosupo.jp/problem/division_of_polynomials
#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "external/fast_io_nor.hpp"
#include "math/polynomial/euclidean_division.hpp"

constexpr int N = 1 << 20;
constexpr uint32_t md = 998244353;

uint32_t f[N], g[N], c1[N], c2[N], c3[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> f[i];
    for (int i = 0; i < m; ++i) cin >> g[i];

    if (m > n) {
        cout << 0 << ' ' << n << '\n';
        cout << '\n';
        for (int i = 0; i < n; ++i) cout << f[i] << " \n"[i == n - 1];
    } else {
        int k = __lg(max(1, n - m)) + 1, k2 = __lg(max(1, n - 1)) + 1;
        div_mod_via_montgomery<md>(f, g, n, m, k, k2, c1, c2, c3);

        int dq = n - m + 1, dr = m - 1;
        while (dq && !f[dq - 1]) --dq;
        while (dr && !g[dr - 1]) --dr;

        cout << dq << ' ' << dr << '\n';
        for (int i = 0; i < dq; ++i) cout << f[i] << " \n"[i == dq - 1];
        for (int i = 0; i < dr; ++i) cout << g[i] << " \n"[i == dr - 1];
    }

    
    return 0;
}