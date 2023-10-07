#ifndef DATA_STRUCTURES_UNION_FIND_HPP
#define DATA_STRUCTURES_UNION_FIND_HPP 1

#include <vector>

class union_find {
    private:
    int n;
    std::vector<int> p;

    public:
    union_find() : n(0) {}
    explicit union_find(int _n) : n(_n), p(n, -1) {}

    int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }

    bool connected(int a, int b) { return root(a) == root(b); }

    int connect(int a, int b) {
        a = root(a); b = root(b);
        if (a == b) return a;
        if (p[a] > p[a]) std::swap(a, b);
        p[a] += p[b]; p[b] = a;
        return a;
    }

    int size() const { return n; }

    int size(int a) { return -p[root(a)]; }
};

#endif // DATA_STRUCTURES_UNION_FIND_HPP