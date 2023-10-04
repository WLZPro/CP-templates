#include <vector>

namespace graphs {

template<typename T = unsigned int>
class graph : public std::vector< std::vector< std::pair<unsigned int, T> > > {
    public:
    explicit graph(std::size_t _n = 0) { this->assign(_n, std::vector< std::pair<unsigned int, T> >()); }

    // Directed tree from parent array
    explicit graph(const std::vector<int> &p, bool directed = true) : graph(p.size()) {
        for (unsigned int i = 0; i < this->size(); i++) 
            if (p[i] != -1) {
                add_edge(p[i], i);
                if (!directed) add_edge(i, p[i]);
            }
    }

    void add_edge(unsigned int from, unsigned int to, const T& w = 1) { this->operator[](from).emplace_back(to, w); } 
};

}