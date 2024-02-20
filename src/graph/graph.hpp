#pragma once

#include <vector>
#include <utility>

class graph : public std::vector< std::vector<int> > {
    public:
    using weight_type = int;
    using std::vector< std::vector<int> >::vector;

    void add_edge(int u, int v) { (*this)[u].push_back(v); }

    int get_end(int v) const { return v; }
    int get_weight(int) const { return 1; }
};

template<typename W>
class weighted_graph : public std::vector< std::vector< std::pair<int, W> > > {
    public:
    using weight_type = W;
    using std::vector< std::vector< std::pair<int, W> > >::vector;

    void add_edge(int u, int v) { (*this)[u].emplace_back(v, W()); }
    void add_edge(int u, int v, const W &w) { (*this)[u].emplace_back(v, w); }

    int get_end(const std::pair<int, W> &p) const { return p.first; }
    W get_weight(const std::pair<int, W> &p) const { return p.second; }
};

template<typename T> constexpr bool is_weighted_graph_v = false;
template<typename W> constexpr bool is_weighted_graph_v< weighted_graph<W> > = true;