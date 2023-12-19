// https://judge.yosupo.jp/problem/lca
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "graph/graph.hpp"
#include "graph/lca_jump_pointers.hpp"
#include "util/fast_io.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    graph g(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        g.add_edge(p, i);
    }

    lowest_common_ancestor lca(g);
    
    while (q--) {
        int u, v; cin >> u >> v;
        cout << lca.query(u, v) << '\n';
    }

    return 0;
}