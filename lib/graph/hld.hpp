#pragma once

#include "data_structure/segment_tree_lazy.hpp"
#include "graph/graph.hpp"

// https://cp-algorithms.com/graph/hld.html
template<typename _Mn = _null_t, typename _Hm = id_map<typename _Mn::T>, typename Graph = graph>
class heavy_light_decomposition {
    using T = typename _Mn::T;
    using F = typename _Hm::T;
    using W = typename Graph::weight_type;

    public:
    using value_type = T;
    using mapping_type = F;
    using weight_type = W;

    heavy_light_decomposition() {}

    heavy_light_decomposition(const Graph &g) : heavy_light_decomposition(g, std::vector<T>(static_cast<int>(g.size()))) {}

    heavy_light_decomposition(const Graph &g, const std::vector<T> &a)
     : n(static_cast<int>(g.size())), p(n, -1), sz(n, 1), d(n, 0), heavy(n, -1), head(n), tin(n) {
        if constexpr (is_weighted_graph_v<Graph>) wd.assign(n, W());

        auto dfs_sizes = [&](auto &&self, int u) -> void {
            for (auto &out_edge : g[u]) {
                int v = g.get_end(out_edge);
                if (v == p[u]) continue;

                p[v] = u; d[v] = d[u] + 1;
                if constexpr (is_weighted_graph_v<Graph>) wd[v] = wd[u] + g.get_weight(out_edge);
                self(self, v);
                sz[u] += sz[v];
                if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) heavy[u] = v;
            }
        };

        int tt = 0;
        auto dfs_decompose = [&](auto &&self, int u, int h) -> void {
            tin[u] = tt++; head[u] = h;
            if (heavy[u] != -1) self(self, heavy[u], h);
            for (auto &out_edge : g[u]) {
                int v = g.get_end(out_edge);
                if (v == p[u] || v == heavy[u]) continue;
                self(self, v, v);
            }
        };

        for (int r = 0; r < n; r++) 
            if (p[r] == -1) {
                p[r] = r;
                dfs_sizes(dfs_sizes, r);
                dfs_decompose(dfs_decompose, r, r);
            }
        
        if constexpr (!std::is_same_v<_Mn, _null_t>) {
            std::vector<T> b(n);
            for (int i = 0; i < n; i++) b[tin[i]] = a[i];
            st_down = lazy_segtree<_Mn, _Hm>(b);
            std::reverse(b.begin(), b.end());
            st_up = lazy_segtree<_Mn, _Hm>(b);
        }
    }

    void set(int u, const T &val) { st_down.set(tin[u], val); st_up.set(n - tin[u] - 1, val); }

    void update_all(const F &f) { st_down.update_all(f); st_up.update_all(f); }

    void update(int u, const F &f) { st_down.update(tin[u], f); st_up.update(n - tin[u] - 1, f); }

    // Warning: arbitary order
    T query_all() const { return st_down.query_all(); }

    T query(int u) { return st_down[tin[u]]; }
    T operator[](int u) { return st_down[tin[u]]; }

    T query_path(int u, int v) {
        T ans_up, ans_down;
        bool up_def = false, down_def = false;

        while (head[u] != head[v])
            if (d[head[u]] > d[head[v]]) {
                if (!up_def) ans_up = st_up.query(n - tin[u] - 1, n - tin[head[u]] - 1), up_def = true;
                else ans_up = _Mn::op(ans_up, st_up.query(n - tin[u] - 1, n - tin[head[u]] - 1));
                u = p[head[u]];
            } else {
                if (!down_def) ans_down = st_down.query(tin[head[v]], tin[v]), down_def = true;
                else ans_down = _Mn::op(st_down.query(tin[head[v]], tin[v]), ans_down);
                v = p[head[v]];
            }

        if (d[u] > d[v]) 
            if (!up_def) ans_up = st_up.query(n - tin[u] - 1, n - tin[v] - 1), up_def = true;
            else ans_up = _Mn::op(ans_up, st_up.query(n - tin[u] - 1, n - tin[v] - 1));
        else {
            if (!down_def) ans_down = st_down.query(tin[u], tin[v]), down_def = true;
            else ans_down = _Mn::op(st_down.query(tin[u], tin[v]), ans_down);
        }

        if (!down_def) return ans_up;
        if (!up_def) return ans_down;
        return _Mn::op(ans_up, ans_down);
    }

    void update_path(int u, int v, const F &f) {
        for (; head[u] != head[v]; v = p[head[v]]) {
            if (d[head[u]] > d[head[v]]) std::swap(u, v);
            st_down.update(tin[head[v]], tin[v], f);
            st_up.update(n - tin[v] - 1, n - tin[head[v]] - 1, f);
        }
        if (d[u] > d[v]) std::swap(u, v);
        st_down.update(tin[u], tin[v], f);
        st_up.update(n - tin[v] - 1, n - tin[u] - 1, f);
    }

    // Warning: arbitary order
    T query_subtree(int u) { return st_down.query(tin[u], tin[u] + sz[u] - 1); }

    // Warning: arbitary order
    void update_subtree(int u, const F &f) {
        st_down.update(tin[u], tin[u] + sz[u] - 1, f);
        st_up.update(tin[u], tin[u] + sz[u] - 1, f);
    }

    int lca(int u, int v) const {
        for (; head[u] != head[v]; v = p[head[v]]) if (d[head[u]] > d[head[v]]) std::swap(u, v);
        return d[u] < d[v] ? u : v;
    }
    int lca(int u, int v, int r) const { return lca(u, v) ^ lca(u, r) ^ lca(v, r); }

    const W &depth(int u) const {
        if constexpr (is_weighted_graph_v<Graph>) return wd[u];
        else return d[u];
    }
    int unweighted_depth(int u) const { return d[u]; }

    W dist(int u, int v) const {
        if constexpr (is_weighted_graph_v<Graph>) return wd[u] + wd[v] - wd[lca(u, v)] * 2;
        else return d[u] + d[v] - d[lca(u, v)] * 2;
    }
    int unweighted_dist(int u, int v) const { return d[u] + d[v] - d[lca(u, v)] * 2; }

    int subtree_size(int u) const { return sz[u]; }
    int dfs_in(int u) const { return tin[u]; }
    int dfs_out(int u) const { return tin[u] + sz[u] - 1; }
    int size() const { return n; }

    private:
    int n;
    std::vector<int> p, sz, d, heavy, head, tin;
    std::vector<W> wd;
    lazy_segtree<_Mn, _Hm> st_down, st_up;
};