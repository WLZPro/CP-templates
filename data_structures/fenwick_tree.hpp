#pragma once

#include "util/abstract_types.hpp"

#include <vector>

template<typename _Ag>
class fenwick_tree {
    public:
    using T = typename _Ag::T;

    fenwick_tree() : n(0) {}
    explicit fenwick_tree(int _n) : n(_n), fenw(n, _Ag::e) {
        #ifdef DEBUG
        _dbg.assign(n, _Ag::e);
        #endif
    }
    
    void update(int idx, const T &val) {
        #ifdef DEBUG
        _dbg[idx] = _Ag::op(_dbg[idx], val);
        #endif

        for (; idx < n; idx |= (idx + 1)) fenw[idx] = _Ag::op(fenw[idx], val);
    }

    T query(int idx) const {
        T ans = _Ag::e;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ans = _Ag::op(ans, fenw[idx]);
        return ans;
    }

    T query(int l, int r) const {
        if (l > r) return _Ag::e;
        if (l == 0) return query(r);
        return _Ag::op(query(r), _Ag::inv(query(l - 1)));
    };

    T operator[](int idx) const { return query(idx, idx); }

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