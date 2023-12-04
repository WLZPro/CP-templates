#pragma once

#include "util/abstract_types.hpp"

#include <vector>
#include <string>

template<typename _Mn, typename _Hm>
class lazy_segment_tree {
    using T = typename _Mn::T;
    using F = typename _Hm::T;

    public:
    using value_type = T;
    using mapping_type = F;

    lazy_segment_tree() : n(0) {}
    
    explicit lazy_segment_tree(int _n)
        : lg((sizeof(int) << 3) - __builtin_clz(_n)), n(1 << lg), len(_n),
          st(n << 1, _Mn::e), lazy(n, _Hm::id) {
        #ifdef DEBUG
        _dbg.assign(n << 1, _Mn::e);
        #endif
    }

    template<typename ...Args>
    explicit lazy_segment_tree(Args &&...args) {
        std::vector<T> a(args...);

        #ifdef DEBUG
        _dbg = a;
        #endif

        if (a.empty()) {
            n = len = 0;
            st = {}; lazy = {};
            return;
        }

        len = static_cast<int>(a.size());
        lg = (sizeof(int) << 3) - __builtin_clz(len);
        n = 1 << lg;

        st.resize(n << 1);
        std::copy(a.begin(), a.end(), st.begin() + n);
        std::fill(st.begin() + n + len, st.end(), _Mn::e);
        for (int i = n - 1; i > 0; i--) pull(i);

        lazy.assign(n, _Hm::id);        
    }

    void set(int idx, const T &val) {
        #ifdef DEBUG
        _dbg[idx] = val;
        #endif

        idx += n;
        for (int i = lg; i > 0; i--) push(idx >> i);
        st[idx] = val;
        for (int i = 1; i <= lg; i++) pull(idx >> i);
    }

    void update_all(const F &f) { update(0, len - 1, f); }

    void update(int idx, const F &f) {
        #ifdef DEBUG
        _dbg[idx] = _Hm::map(f, _dbg[idx]);
        #endif

        idx += n;
        for (int i = lg; i > 0; i--) push(idx >> i);
        st[idx] = _Hm::map(f, st[idx]);
        for (int i = 1; i <= lg; i++) pull(idx >> i);
    }

    void update(int l, int r, const F &f) {
        #ifdef DEBUG
        for (int i = l; i <= r; i++) _dbg[i] = _Hm::map(f, _dbg[i]);
        #endif

        l += n; r += n + 1;

        for (int i = lg; i > 0; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int tmp_l = l, tmp_r = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(f, l++);
            if (r & 1) apply(f, --r);
        }
        l = tmp_l; r = tmp_r;

        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) pull(l >> i);
            if (((r >> i) << i) != r) pull((r - 1) >> i);
        }
    }

    const T &query_all() const { return st[1]; }

    const T &query(int idx) {
        idx += n;
        for (int i = lg; i > 0; i--) push(idx >> i);
        return st[idx];
    }

    T query(int l, int r) {
        l += n; r += n + 1;

        for (int i = lg; i > 0; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        T ans_l, ans_r;
        bool l_def = false, r_def = false;
        for (; l < r; l >>= 1, r >>= 1) {
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

    const T &operator[](int idx) { return query(idx); }

    int size() const { return len; }

    friend std::string to_string(const lazy_segment_tree &st) {
        #ifdef DEBUG
        return to_string(st._dbg);
        #else
        return "";
        #endif
    }

    private:
    int lg, n, len;
    std::vector<T> st;
    std::vector<F> lazy;

    #ifdef DEBUG
    std::vector<T> _dbg;
    #endif

    inline void pull(int idx) { st[idx] = _Mn::op(st[idx << 1], st[idx << 1 | 1]); }

    inline void apply(const F &f, int idx) {
        st[idx] = _Hm::map(f, st[idx]);
        if (idx < n) lazy[idx] = _Hm::comp(f, lazy[idx]);
    }

    inline void push(int idx) {
        apply(lazy[idx], idx << 1); apply(lazy[idx], idx << 1 | 1);
        lazy[idx] = _Hm::id;
    }
};

template<typename _Mn, typename _Hm> using lazy_segtree = lazy_segment_tree<_Mn, _Hm>;