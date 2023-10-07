#ifndef GRAPHS_GRAPHS_HPP
#define GRAPHS_GRAPHS_HPP 1

#include <vector>

namespace graphs {

template<typename T>
struct out_edge {
    int to; T w;
    explicit out_edge(int _to, const T &_w = 1) : to(_to), w(_w) {}
};

template<typename T>
struct edge {
    int from, to; T w;
    edge(int _from, int _to, const T &_w = 1) : from(_from), to(_to), w(_w) {}
};

template<typename T = int>
class graph : public std::vector< std::vector< out_edge<T> > > {
    public:
    explicit graph(int _n = 0) { this->assign(_n, std::vector< out_edge<T> >()); }

    // Directed tree from parent array
    explicit graph(const std::vector<int> &p, bool directed = true) : graph(static_cast<int>(p.size())) {
        for (int i = 0; i < static_cast<int>(this->size()); i++)
            if (p[i] != -1) {
                add_edge(p[i], i);
                if (!directed) add_edge(i, p[i]);
            }
    }

    void add_edge(int from, int to, const T& w = 1) { this->operator[](from).emplace_back(to, w); } 

    std::vector< edge<T> > edges(bool directed = true) const {
        std::vector< edge<T> > ans;
        int n = static_cast<int>(this->size());
        for (int i = 0; i < n; i++) for (auto &[to, w] : this->operator[](i)) if (directed || to >= i) ans.emplace_back(i, to, w);
        return ans;
    }
};

}

#endif // GRAPHS_GRAPHS_HPP