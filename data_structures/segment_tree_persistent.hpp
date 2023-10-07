#ifndef DATA_STRUCTURES_SEGMENT_TREE_PERSISTENT_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_PERSISTENT_HPP 1

#include <vector>
#include <functional>
#include <numeric>

template<typename T> constexpr T my_add(T a, T b) { return a + b; }

template<typename T, auto f = my_add<T> >
class persistent_segment_tree {
    static_assert(std::is_convertible_v<decltype(f), std::function<T(T, T)> >);

    private:
    int n, root;
    std::vector<T> st;
    std::vector<int> lc, rc;

    int build(int cl, int cr, const std::vector<T> &a) {
        if (cl + 1 == cr) {
            st.push_back(a[cl]); lc.push_back(0); rc.push_back(0);
            return static_case<int>(st.size()) - 1;
        }
        int cm = (cl + cr) >> 1;
        int tmp_l = build(cl, cm, a), tmp_r = build(cm, cr, a);
        lc.push_back(tmp_l); rc.push_back(tmp_r);
        st.push_back(f(st[tmp_l], st[tmp_r]));
        return static_cast<int>(st.size()) - 1;
    }

    T query(int idx, int cl, int cr, int l, int r) const {
        if (l <= cl && cr <= r) return st[idx];
        int cm = (cl + cr) >> 1;
        if (r <= cm) return query(lc[idx], cl, cm, l, r);
        if (l >= cm) return query(rc[idx], cm, cr, l, r);
        return f(query(lc[idx], cl, cm, l, r), query(rc[idx], cm, cr, l, r));
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
        st.push_back(f(st[tmp_l], st[tmp_r]));
        return static_cast<int>(st.size()) - 1;
    }

    public:
    // Note: hasn't been tested yet
    persistent_segment_tree() : n(0) {}
    
    explicit persistent_segment_tree(const std::vector<T> &a) : n(static_cast<int>(a.size())) { root = build(0, n, a); }

    // Note: hasn't been tested yet
    explicit persistent_segment_tree(int _n) : persistent_segment_tree(std::vector<T>(_n)) {}

    persistent_segment_tree(int _n, const T &x) : persistent_segment_tree(std::vector<T>(_n, x)) {}

    int original_root() const { return root; }

    T query(int idx, int l, int r) const { return query(idx, 0, n, l, r); }

    // Note: hasn't been tested yet
    T query(int idx, int l) const { return query(idx, l, l + 1); }

    int update(int idx, int pos, const T &val) { return update(idx, 0, n, pos, val); }

    // Note: hasn't been tested yet
    int size() const { return n; }
};

#endif // DATA_STRUCTURES_SEGMENT_TREE_PERSISTENT_HPP