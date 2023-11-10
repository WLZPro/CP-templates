#pragma once
#line 2 "data_structures/fenwick_tree.hpp"

#include <vector>
#include <string>
#include <functional>

template<typename T>
struct _ft_zero {
    constexpr T operator()() { return 0; };
};

template<typename T, typename F = std::plus<T>, typename FRev = std::minus<T>, typename E = _ft_zero<T> >
class fenwick_tree {
    private:
    static constexpr F f = F();
    static constexpr FRev f_rev = FRev();
    static constexpr T e = E()();

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

    void update(int idx, const T &val) {
        for (; idx < n; idx |= (idx + 1)) fenw[idx] = f(fenw[idx], val);

        #ifdef DEBUG
        debug[idx] = f(debug[idx], val);
        #endif
    }

    T query(int idx) const {
        T ans = e;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ans = f(ans, fenw[idx]);
        return ans;
    }

    T query(int l, int r) const {
        if (l == 0) return query(r);
        return f_rev(query(r), query(l - 1));
    }

    int lower_bound(const T &x); // TO DO

    const int &size() const { return n; }

    inline friend std::string to_string(const fenwick_tree &fenw) {
        #ifdef DEBUG
        return to_string(fenw.debug);
        #else
        return "";
        #endif
    }
};