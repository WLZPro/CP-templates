#pragma once

#include "util/abstract_types.hpp"

#include <vector>
#include <functional>

// https://github.com/the-tourist/algo/blob/master/data/fenwick.cpp
template<typename G>
class fenwick_tree {
    public:
    using T = typename G::T;

    fenwick_tree() : n(0) {}
    explicit fenwick_tree(int _n) : n(_n), fenw(n, G::e) {
        #ifdef DEBUG
        _dbg.assign(n, G::e);
        #endif
    }
    
    // https://codeforces.com/blog/entry/63064
    explicit fenwick_tree(const std::vector<T> &a) : fenwick_tree(a.size()) {
        #ifdef DEBUG
        _dbg = a;
        #endif

        for (int i = 0; i < n; i++) {
            fenw[i] = G::op(fenw[i], a[i]);
            if ((i | (i + 1)) < n) fenw[i | (i + 1)] = G::op(fenw[i | (i + 1)], fenw[i]);
        }
    }

    void update(int idx, const T &val) {
        #ifdef DEBUG
        _dbg[idx] = G::op(_dbg[idx], val);
        #endif

        for (; idx < n; idx |= (idx + 1)) fenw[idx] = G::op(fenw[idx], val);
    }

    T query(int idx) const {
        T ans = G::e;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ans = G::op(ans, fenw[idx]);
        return ans;
    }

    T query(int l, int r) const {
        l = std::max(0, l); r = std::min(n - 1, r);
        if (l > r) return G::e;
        if (l == 0) return query(r);
        return G::op(query(r), G::inv(query(l - 1)));
    };

    T operator[](int idx) const { return query(idx, idx); }

    // https://codeforces.com/blog/entry/61364
    // Find smallest `i` s.t. `p(a[0..i])` is true (`n` if no such `i`)
    // Assumptions: `n > 0`, `p(a[0..i])` implies `p(a[0..i+1])`
    template<typename P>
    int search(const P &p) const {
        // static_assert(std::is_convertible_v<P, std::function<bool(T)> >,
        //               "p must be a unary predicate function");
        int idx = -1; T v = G::e, nv;
        for (int i = __lg(n); i >= 0; --i) 
            if ((idx + (1 << i)) < n && !p(nv = G::op(v, fenw[idx + (1 << i)]))) 
                idx += 1 << i, v = nv;
        return idx + 1;
    }

    friend std::string to_string(const fenwick_tree &ft) {
        #ifdef DEBUG
        return to_string(ft._dbg);
        #else
        return "";
        #endif
    }

    private:
    int n;
    std::vector<T> fenw;

    #ifdef DEBUG
    std::vector<T> _dbg;
    #endif
};