#pragma once

#include "graph/graph.hpp"

#include <algorithm>

// https://cp-algorithms.com/graph/lca_farachcoltonbender.html
template<typename Graph = graph>
class lowest_common_ancestor {
    using W = typename Graph::weight_type;

    public:
    using weight_type = W;

    lowest_common_ancestor() {}

    explicit lowest_common_ancestor(const Graph &g)
     : n(static_cast<int>(g.size())), first_visit(n, -1), d(n, 0), euler_tour(n << 1), lg(n << 1) {
        if constexpr (is_weighted_graph_v<Graph>) wd.assign(n, W());
        int euler_tour_sz = 0;

        auto dfs = [&](auto &&self, int u, int p) -> void {
            first_visit[u] = euler_tour_sz;
            euler_tour[euler_tour_sz++] = u;

            for (const auto &out_edge : g[u]) {
                int v = g.get_end(out_edge);
                if (v == p) continue;
                d[v] = d[u] + 1;
                self(self, v, u);
                euler_tour[euler_tour_sz++] = u;
            }
        };

        for (int r = 0; r < n; r++) if (first_visit[r] == -1) dfs(dfs, r, -1);

        lg[0] = -1;
        for (int i = 1; i <= euler_tour_sz; i++) lg[i] = lg[i >> 1] + 1;

        block_sz = std::max(1, lg[euler_tour_sz] >> 1);
        block_cnt = (euler_tour_sz + block_sz - 1) / block_sz;

        st.resize((lg[block_cnt] + 1) * block_cnt);
        block_mask.assign(block_cnt, 0);
        for (int i = 0, j = 0, b = 0, bit = 1; i < euler_tour_sz; i++, j++, bit <<= 1) {
            if (j == block_sz) j = 0, b++;
            if (j == 1) bit = 1;
            if (j == 0 || mn(i, st[b]) == i) st[b] = i;
            if (j > 0 && (i >= euler_tour_sz || mn(i - 1, i) == i - 1)) block_mask[b] |= bit;
        }

        for (int k = 1, len = 1, idx = block_cnt; k <= lg[block_cnt]; k++, len <<= 1) {
            for (int b = 0; b < block_cnt; b++, idx++) {
                if (b + len >= block_cnt) st[idx] = st[idx - block_cnt];
                else st[idx] = mn(st[idx - block_cnt], st[idx - block_cnt + len]);
            }
        }

        blocks.resize(1 << (block_sz - 1));
        for (int b = 0; b < block_cnt; b++) {
            int mask = block_mask[b];
            if (!blocks[mask].empty()) continue;
            blocks[mask].assign(block_sz, std::vector<int>(block_sz));
            for (int l = 0; l < block_sz; l++) {
                blocks[mask][l][l] = l;
                for (int r = l + 1; r < block_sz; r++) {
                    blocks[mask][l][r] = blocks[mask][l][r - 1];
                    if (b * block_sz + r < euler_tour_sz) blocks[mask][l][r] = mn(b * block_sz + blocks[mask][l][r], b * block_sz + r) - b * block_sz;
                }
            }
        }
    }

    int query(int u, int v) const {
        int l = first_visit[u], r = first_visit[v];
        if (l > r) std::swap(l, r);

        auto internal_query = [&](int b, int _l, int _r) {
            return blocks[block_mask[b]][_l][_r] + b * block_sz;
        };

        int bl = l / block_sz, br = r / block_sz;
        if (bl == br) return euler_tour[internal_query(bl, l % block_sz, r % block_sz)];
        int ans = mn(internal_query(bl, l % block_sz, block_sz - 1), internal_query(br, 0, r % block_sz));
        if (bl + 1 < br) {
            int k = lg[br - bl - 1];
            ans = mn(ans, mn(st[k * block_cnt + bl + 1], st[k * block_cnt + br - (1 << k)]));
        }
        return euler_tour[ans];
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

    private:
    int n, block_sz, block_cnt;
    std::vector<int> first_visit, d, euler_tour, lg, block_mask, st;
    std::vector< std::vector< std::vector<int> > > blocks;
    std::vector<W> wd;

    inline int mn(int a, int b) const { return d[euler_tour[a]] < d[euler_tour[b]] ? a : b; }
};