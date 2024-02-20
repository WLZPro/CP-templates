#pragma once

#include "util/abstract_types.hpp"

#include <vector>

template<typename _Mn>
class segment_tree {
    using T = typename _Mn::T;

    public:
    using value_type = T;

    segment_tree() : n(0) {};
    explicit segment_tree(int _n) : n(_n), st(n << 1, _Mn::e) {
        #ifdef DEBUG
        _dbg.assign(n, _Mn::e);
        #endif
    }
    
    template<typename ...Args>
    explicit segment_tree(Args &&...args) {
        std::vector<T> a(args...);
        
        #ifdef DEBUG
        _dbg = a;
        #endif

        n = static_cast<int>(a.size());
        st.resize(n << 1); std::copy(a.begin(), a.end(), st.begin() + n);

        for (int i = n - 1; i > 0; i--) st[i] = _Mn::op(st[i << 1], st[i << 1 | 1]);
    }
    
    void update(int idx, const T &val) {
        #ifdef DEBUG
        _dbg[idx] = val;
        #endif

        for (st[idx += n] = val; idx >>= 1; ) st[idx] = _Mn::op(st[idx << 1], st[idx << 1 | 1]);
    }

    // Warning: arbitary order
    const T &query_all() const { return st[1]; }

    const T &query(int idx) const { return st[idx + n]; }

    const T &operator[](int idx) const { return st[idx + n]; }

    T query(int l, int r) const {
        if (l > r) return _Mn::e;

        T ans_l, ans_r;
        bool l_def = false, r_def = false;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                if (!l_def) ans_l = st[l++], l_def = true;
                else ans_l = _Mn::op(ans_l, st[l++]);
            }
            if (r & 1) {
                if (!r_def) ans_r = st[--r], r_def = true;
                else ans_r = _Mn::op(st[--r], ans_r);
            }
        }

        if (!l_def) return ans_r;
        if (!r_def) return ans_l;
        return _Mn::op(ans_l, ans_r);
    }

    int size() const { return n; }

    friend std::string to_string(const segment_tree &st) {
        #ifdef DEBUG
        return to_string(st._dbg);
        #else
        return "";
        #endif
    }

    private:
    int n;
    std::vector<T> st;

    #ifdef DEBUG
    std::vector<T> _dbg;
    #endif
};

template<typename _Mn> using segtree = segment_tree<_Mn>;