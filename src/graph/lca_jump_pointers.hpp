#pragma once

#include "graph/graph.hpp"

// https://codeforces.com/blog/entry/74847
template<typename Graph = graph>
class lowest_common_ancestor {
    using W = typename Graph::weight_type;

    public:
    using weight_type = W;

    lowest_common_ancestor() {}

    explicit lowest_common_ancestor(const Graph &g)
     : n(static_cast<int>(g.size())), p(n, -1), jump(n, -1), d(n, 0) {
        if constexpr (is_weighted_graph_v<Graph>) wd.assign(n, W());

        auto dfs = [&](auto &&self, int u) -> void {
            jump[u] = p[u];
            if (2 * d[jump[p[u]]] == d[p[u]] + d[jump[jump[p[u]]]]) jump[u] = jump[jump[p[u]]];

            for (auto &out_edge : g[u]) {
                int v = g.get_end(out_edge);

                if (v == p[u]) continue;
                p[v] = u; d[v] = d[u] + 1;
                if constexpr (is_weighted_graph_v<Graph>) wd[v] = wd[u] + g.get_weight(out_edge);
                self(self, v);
            }
        };

        for (int r = 0; r < n; r++) if (p[r] == -1) p[r] = r, dfs(dfs, r);
    }

    int kth_ancestor(int u, int k) const {
        int v = u;
        while (d[u] - d[v] < k) {
            if (d[u] - d[jump[v]] < k) v = jump[v];
            else v = p[v];
        }
        return v;
    }

    int query(int u, int v) const {
        if (d[u] < d[v]) return query(v, u);
        u = kth_ancestor(u, d[u] - d[v]);
        while (u != v) {
            if (jump[u] == jump[v]) u = p[u], v = p[v];
            else u = jump[u], v = jump[v];
        }
        return u;
    }

    int query(int u, int v, int r) const { return query(u, v) ^ query(u, r) ^ query(v, r); }

    const W &depth(int u) const {
        if constexpr (is_weighted_graph_v<Graph>) return wd[u];
        else return d[u];
    }

    W dist(int u, int v) const  {
        if constexpr (is_weighted_graph_v<Graph>) return wd[u] + wd[v] - wd[query(u, v)] * 2;
        else return d[u] + d[v] - d[query(u, v)] * 2;
    }

    int unweighted_depth(int u) const { return d[u]; }
    int unweighted_dist(int u, int v) const { return d[u] + d[v] - d[query(u, v)] * 2; }

    int size() const { return n; }

    public:
    int n;
    std::vector<int> p, jump, d;
    std::vector<W> wd;
};