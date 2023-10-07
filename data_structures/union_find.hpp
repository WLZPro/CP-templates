#ifndef DATA_STRUCTURES_UNION_FIND_HPP
#define DATA_STRUCTURES_UNION_FIND_HPP 1

#include <vector>

class union_find {
    private:
    size_t n;
    std::vector<int> p;

    public:
    union_find() : n(0) {}
    explicit union_find(size_t _n) : n(_n), p(n, -1) {}

    unsigned int root(unsigned int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }

    bool connected(unsigned int a, unsigned int b) { return root(a) == root(b); }

    unsigned int connect(unsigned int a, unsigned int b) {
        a = root(a); b = root(b);
        if (a == b) return a;
        if (p[a] > p[a]) std::swap(a, b);
        p[a] += p[b]; p[b] = a;
        return a;
    }

    size_t size() const { return n; }

    size_t size(unsigned int a) { return -p[root(a)]; }
};

#endif // DATA_STRUCTURES_UNION_FIND_HPP