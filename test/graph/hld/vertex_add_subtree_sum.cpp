// https://judge.yosupo.jp/problem/vertex_add_subtree_sum
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "graph/hld.hpp"
#include "math/modint.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    graph g(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        g.add_edge(p, i);
    }

    heavy_light_decomposition< addition<long long>, addition_with_sum<long long> > hld(g, a);

    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int u, x; cin >> u >> x;
            hld.update(u, x);
        } else {
            int u; cin >> u;
            cout << hld.query_subtree(u) << '\n';
        }
    }

    return 0;
}