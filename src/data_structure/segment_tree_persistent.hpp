#pragma once

#include "util/abstract_types.hpp"

#include <vector>

template<typename _Sg>
class persistent_segment_tree {
    using T = typename _Sg::T;

    public:
    using value_type = T;

    persistent_segment_tree() : n(0) {}

    template<typename ...Args>
    explicit persistent_segment_tree(Args &&...args) {
        std::vector<T> a(args...);

        n = static_cast<int>(a.size());
        st.reserve(n << 1); lc.reserve(n << 1); rc.reserve(n << 1);

        root = build(0, n, a);
    }

    int original_root() const { return root; }

    T query(int rt, int l, int r) const { return query(rt, 0, n, l, r); }

    T query(int rt, int l) const { return query(rt, l, l); }

    int update(int rt, int pos, const T &val) { return update(rt, 0, n, pos, val); }

    int size() const { return n; }

    private:
    int n, root;
    std::vector<T> st;
    std::vector<int> lc, rc;

    int build(int cl, int cr, const std::vector<T> &a) {
        if (cl + 1 == cr) {
            st.push_back(a[cl]); lc.push_back(0); rc.push_back(0);
            return static_cast<int>(st.size()) - 1;
        }
        int cm = (cl + cr) >> 1;
        int tmp_l = build(cl, cm, a), tmp_r = build(cm, cr, a);
        lc.push_back(tmp_l); rc.push_back(tmp_r);
        st.push_back(_Sg::op(st[tmp_l], st[tmp_r]));
        return static_cast<int>(st.size()) - 1;
    }

    T query(int idx, int cl, int cr, int l, int r) const {
        if (l <= cl && cr <= r + 1) return st[idx];
        int cm = (cl + cr) >> 1;
        if (r <  cm) return query(lc[idx], cl, cm, l, r);
        if (l >= cm) return query(rc[idx], cm, cr, l, r);
        return _Sg::op(query(lc[idx], cl, cm, l, r), query(rc[idx], cm, cr, l, r));
    }

    int update(int idx, int cl, int cr, int pos, const T &val) {
        if (cl + 1 == cr) {
            st.push_back(val); lc.push_back(0); rc.push_back(0);
            return static_cast<int>(st.size()) - 1;
        }
        int cm = (cl + cr) >> 1;
        int tmp_l = lc[idx], tmp_r = rc[idx];
        if (pos < cm) tmp_l = update(lc[idx], cl, cm, pos, val);
        else tmp_r = update(rc[idx], cm, cr, pos, val);
        lc.push_back(tmp_l); rc.push_back(tmp_r);
        st.push_back(_Sg::op(st[tmp_l], st[tmp_r]));
        return static_cast<int>(st.size()) - 1;
    }
};

template<typename _Sg> using persistent_segtree = persistent_segment_tree<_Sg>;
template<typename _Sg> using psegtree = persistent_segtree<_Sg>;