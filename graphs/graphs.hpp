#include <vector>

namespace graphs {

template<typename T>
struct out_edge {
    unsigned int to; T w;
    explicit out_edge(unsigned int _to, const T &_w = 1) : to(_to), w(_w) {}
};

template<typename T>
struct edge {
    unsigned int from, to; T w;
    edge(unsigned int _from, unsigned int _to, const T &_w = 1) : from(_from), to(_to), w(_w) {}
};

template<typename T = unsigned int>
class graph : public std::vector< std::vector< out_edge<T> > > {
    public:
    explicit graph(std::size_t _n = 0) { this->assign(_n, std::vector< out_edge<T> >()); }

    // Directed tree from parent array
    explicit graph(const std::vector<int> &p, bool directed = true) : graph(p.size()) {
        for (unsigned int i = 0; i < this->size(); i++)
            if (p[i] != -1) {
                add_edge(p[i], i);
                if (!directed) add_edge(i, p[i]);
            }
    }

    void add_edge(unsigned int from, unsigned int to, const T& w = 1) { this->operator[](from).emplace_back(to, w); } 

    std::vector< edge<T> > edges(bool directed = true) const {
        std::vector< edge<T> > ans;
        std::size_t n = this->size();
        for (unsigned int i = 0; i < n; i++) for (auto &[to, w] : this->operator[](i)) if (directed || to >= i) ans.emplace_back(i, to, w);
        return ans;
    }
};

}