#ifndef DATA_STRUCTURES_FENWICK_TREE_HPP
#define DATA_STRUCTURES_FENWICK_TREE_HPP 1

#include <vector>
#include <functional>

template<typename T> inline T add(T a, T b) { return a + b; }

template<typename T> inline T sub(T a, T b) { return a - b; }

template<typename T, auto f = add<T>, const T e = 0, auto f_rev = sub<T> >
class fenwick_tree {

    static_assert(std::is_convertible_v<decltype(f), std::function<T(T, T)> >);
    static_assert(std::is_convertible_v<decltype(f_rev), std::function<T(T, T)> >);

    private: 
    int n;
    std::vector<T> fenw;
    #ifdef DEBUG
    std::vector<T> debug;
    #endif
    
    public:
    fenwick_tree() : n(0) {}

    explicit fenwick_tree(int _n) : n(_n) {
        fenw.assign(n, e);
        #ifdef DEBUG
        debug.assign(n, e);
        #endif
    }

    void update(int idx, T x) {
        #ifdef DEBUG
        debug[idx] = f(debug[idx], x);
        #endif
        for (; idx < n; idx |= (idx + 1)) fenw[idx] = f(fenw[idx], x);
    }

    T query(int _idx) const {
        T ans = e;
        for (int idx = _idx; idx >= 0; idx = (idx & (idx + 1)) - 1) ans = f(ans, fenw[idx]);
        return ans;
    }

    T query(int l, int r) const { return f_rev(query(r), l > 0 ? query(l - 1) : e); }

    int size() const { return n; }
};

#endif // DATA_STRUCTURES_FENWICK_TREE_HPP