// https://judge.yosupo.jp/problem/vertex_set_path_composite
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

using mint = modint998244353;

struct linear_function {
    mint a, b;
    mint operator()(mint x) const { return a * x + b; }
};

struct composition {
    using T = linear_function;
    
    static constexpr linear_function e = {1, 0};
    static constexpr linear_function op(const linear_function &f, const linear_function &g) { return {f.a * g.a, f.a * g.b + f.b}; }
};
template<> constexpr bool has_map_with_implicit_size_v<composition> = true;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;

    vector<linear_function> f(n);
    for (int i = 0; i < n; i++) cin >> f[i].a >> f[i].b;

    graph g(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g.add_edge(u, v); g.add_edge(v, u);
    }

    heavy_light_decomposition<composition> hld(g, f);

    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int p; mint c, d; cin >> p >> c >> d;
            hld.set(p, {c, d});
        } else {
            int u, v; mint x; cin >> u >> v >> x;
            cout << hld.query_path(v, u)(x) << '\n';
        }
    }

    return 0;
}