#ifndef GRAPHS_LCA_JUMP_POINTERS_HPP
#define GRAPHS_LCA_JUMP_POINTERS_HPP 1

#include "graphs.hpp"

#include <vector>

namespace graphs {

template<typename T = unsigned int>
class lowest_common_ancestor {
    private:
    graph<T> g;
    std::vector<unsigned int> p, jump, d;
    std::vector<T> wd;

    void dfs(unsigned int u) {
        if (d[p[u]] - d[jump[p[u]]] == d[jump[p[u]]] - d[jump[jump[p[u]]]]) jump[u] = jump[jump[p[u]]];

        for (auto &[v, w] : g[u]) {
            if (v == p[u]) continue;
            jump[v] = p[v] = u;
            d[v] = d[u] + 1;
            wd[v] = wd[u] + w;
            dfs(v);
        }
    }

    public:
    lowest_common_ancestor() {}

    explicit lowest_common_ancestor(const graph<T> &_g, const std::vector<unsigned int> roots = {1}) : g(_g) {
        std::size_t n = g.size();
        p.resize(n); jump.resize(n); d.assign(n, 0); wd.assign(n, 0);
        for (const auto &root : roots) {
            p[root] = root;
            dfs(root);
        }
    }

    unsigned int kth_ancestor(unsigned int u, unsigned int k) const {
        unsigned int v = u;
        while (d[u] - d[v] < k) {
            if (d[u] - d[jump[v]] < k) v = jump[v];
            else v = p[v];
        }
        return v;
    }

    unsigned int query(unsigned int u, unsigned int v) const {
        if (d[u] < d[v]) return query(v, u);
        u = kth_ancestor(u, d[u] - d[v]);
        while (u != v) {
            if (jump[u] == jump[v]) u = p[u], v = p[v];
            else u = jump[u], v = jump[v];
        }
        return u;
    }

    // Note: hasn't been tested yet
    T depth(unsigned int u) const { return wd[u]; }

    // Note: hasn't been tested yet
    T dist(unsigned int u, unsigned int v) const { return wd[u] + wd[v] - 2 * wd[query(u, v)]; }
};

}

#endif // GRAPHS_LCA_JUMP_POINTERS_HPP