#ifndef GRAPHS_LCA_FARACH_COLTON_BENDER
#define GRAPHS_LCA_FARACH_COLTON_BENDER 1

#include "graphs.hpp"

#include <functional>
#include <algorithm>

namespace graphs {

// LCA using the Farach-Colton and Bender Algorithm
// See https://cp-algorithms.com/graph/lca_farachcoltonbender.html
template<typename T>
class lowest_common_ancestor {
    private:
    int n, block_sz, block_cnt;
    graph<T> g;
    std::vector<int> first_visit, d, euler_tour, lg, block_mask, st;
    std::vector< std::vector< std::vector<int> > > blocks;

    int mn(int a, int b) const {
        return d[euler_tour[a]] < d[euler_tour[b]] ? a : b;
    }

    public:
    lowest_common_ancestor() {}

    explicit lowest_common_ancestor(const graph<T> &_g, const std::vector<int> roots = {1})
    : n(static_cast<int>(_g.size())), g(_g), first_visit(n), d(n, 0), euler_tour(n << 1), lg(n << 1) {

        int euler_tour_sz = 0;

        std::function<void(int, int)> dfs = [&](int u, int p) {
            first_visit[u] = euler_tour_sz;
            euler_tour[euler_tour_sz++] = u;

            for (auto &[v, w] : g[u]) {
                if (v == p) continue;
                d[v] = d[u] + 1;
                dfs(v, u);
                euler_tour[euler_tour_sz++] = u;
            }
        };

        for (const int &root : roots) dfs(root, -1);

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
};

};

#endif // GRAPHS_LCA_FARACH_COLTON_BENDER