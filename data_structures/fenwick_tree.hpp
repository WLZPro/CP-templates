#ifndef DATA_STRUCTURES_FENWICK_TREE_HPP
#define DATA_STRUCTURES_FENWICK_TREE_HPP 1

#include <vector>
#include <functional>

template<typename T> constexpr T _fenw_add(const T &a, const T &b) { return a + b; }
template<typename T> constexpr T _fenw_sub(const T &a, const T &b) { return a - b; }
template<typename T> constexpr T _fenw_zero() { return 0; }

template<typename T, auto f = _fenw_add<T>, auto e = _fenw_zero<T>, auto f_rev = _fenw_sub<T> >
class fenwick_tree {
    private: 
    int n;
    std::vector<T> fenw;
    #ifdef DEBUG
    std::vector<T> debug;
    #endif
    
    public:
    fenwick_tree() : n(0) {}

    explicit fenwick_tree(int _n) : n(_n) {
        fenw.assign(n, e());
        #ifdef DEBUG
        debug.assign(n, e());
        #endif
    }

    void update(int idx, T x) {
        #ifdef DEBUG
        debug[idx] = f(debug[idx], x);
        #endif
        for (; idx < n; idx |= (idx + 1)) fenw[idx] = f(fenw[idx], x);
    }

    T query(int idx) const {
        T ans = e();
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ans = f(ans, fenw[idx]);
        return ans;
    }

    T query(int l, int r) const { return f_rev(query(r), l > 0 ? query(l - 1) : e()); }

    int size() const { return n; }
};

#endif // DATA_STRUCTURES_FENWICK_TREE_HPP