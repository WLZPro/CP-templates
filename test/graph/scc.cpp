// https://judge.yosupo.jp/problem/scc
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "graph/graph.hpp"
#include "graph/scc.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g.add_edge(u, v);
    }

    vector< vector<int> > scc = sccs(g);

    cout << scc.size() << '\n';
    for (auto &v : scc) {
        cout << v.size();
        for (auto &x : v) cout << ' ' << x;
        cout << '\n';
    }

    return 0;
}