#pragma once

#include <stack>
#include <algorithm>

#include "graph/graph.hpp"

// https://github.com/atcoder/ac-library/blob/master/atcoder/internal_scc.hpp
template<typename Graph>
std::vector<int> scc_ids(const Graph &g) {
    int n = static_cast<int>(g.size());
    
    int dfs_cnt = 0, scc_cnt = 0;
    std::vector<int> dfs_low(n), dfs_ord(n, -1), scc_id(n);
    std::stack<int> cur_visited;
    auto dfs = [&](auto &&self, int u) -> void {
        dfs_low[u] = dfs_ord[u] = dfs_cnt++;
        cur_visited.push(u);
        for (auto &out_edge : g[u]) {
            int v = g.get_end(out_edge);
            if (dfs_ord[v] == -1) self(self, v), dfs_low[u] = std::min(dfs_low[u], dfs_low[v]);
            else dfs_low[u] = std::min(dfs_low[u], dfs_ord[v]);
        }
        if (dfs_low[u] == dfs_ord[u]) {
            while (true) {
                int v = cur_visited.top(); cur_visited.pop();
                dfs_ord[v] = n; scc_id[v] = scc_cnt;
                if (v == u) break;
            }
            scc_cnt++;
        }
    };

    for (int i = 0; i < n; i++) if (dfs_ord[i] == -1) dfs(dfs, i);
    for (int i = 0; i < n; i++) scc_id[i] = scc_cnt - scc_id[i] - 1;
    return scc_id;
}

template<typename Graph>
std::vector< std::vector<int> > sccs(const Graph &g) {
    std::vector<int> ids = scc_ids(g);
    int scc_cnt = *std::max_element(ids.begin(), ids.end());
    std::vector< std::vector<int> > ans(scc_cnt + 1, std::vector<int>());
    for (int i = 0; i < static_cast<int>(g.size()); i++) ans[ids[i]].push_back(i);
    return ans;
}