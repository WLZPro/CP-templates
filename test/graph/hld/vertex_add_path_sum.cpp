// https://judge.yosupo.jp/problem/vertex_add_path_sum
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "graph/graph.hpp"
#include "graph/hld.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    graph g(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g.add_edge(u, v); g.add_edge(v, u);
    }

    heavy_light_decomposition< addition<long long>, addition_with_sum<long long> > hld(g, a);

    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int p, x; cin >> p >> x;
            hld.update(p, x);
        } else {
            int u, v; cin >> u >> v;
            cout << hld.query_path(u, v) << '\n';
        }
    }

    return 0;
}