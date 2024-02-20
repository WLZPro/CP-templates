#pragma once

#include "graph/graph.hpp"
#include "graph/scc.hpp"

// https://github.com/atcoder/ac-library/blob/master/atcoder/twosat.hpp
class two_sat {
    public:
    two_sat() {}
    two_sat(int _n) : n(_n), g(n << 1), ans(n) {}

    void add(int a, bool sa, int b, bool sb) {
        g.add_edge(a + (sa ? 0 : n), b + (sb ? n : 0));
        g.add_edge(b + (sb ? 0 : n), a + (sa ? n : 0));
    }

    void add(int a, int b) { add(std::abs(a), a > 0, std::abs(b), b > 0); }

    bool satisfiable() {
        std::vector<int> scc = scc_ids(g);
        for (int i = 0; i < n; i++) {
            if (scc[i] == scc[i + n]) return false;
            ans[i] = scc[i] < scc[i + n];
        }
        return true;
    }

    std::vector<bool> answer() const { return ans; }

    int size() const { return n; }

    private:
    int n;
    graph g;
    std::vector<bool> ans;
};