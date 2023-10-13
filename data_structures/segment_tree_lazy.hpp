#ifndef DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP 1

#include <vector>
#include <functional>

// Lazy segment tree implementation based on the [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp).
// Main differences: no identity element required, implemented recursively, no static_asserts.
template<typename T, auto f, typename mp_t, auto apply, auto combine, auto id>
class segment_tree {
    private:
    int n; 
    std::vector<T> st;
    std::vector<mp_t> lazy;

    void build(int idx, int l, int r, const std::vector<T> &a) {
        if (l + 1 == r) {
            st[idx] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(idx << 1, l, m, a); build(idx << 1 | 1, m, r, a);
        st[idx] = f(st[idx << 1], st[idx << 1 | 1]);
    }

    void push(int idx) {
        st[idx] = apply(lazy[idx], st[idx]);
        if ((idx << 1 | 1) < static_cast<int>(lazy.size())) {
            lazy[idx << 1] = combine(lazy[idx], lazy[idx << 1]);
            lazy[idx << 1 | 1] = combine(lazy[idx], lazy[idx << 1 | 1]);
        }
        lazy[idx] = id();
    }

    T query(int idx, int cl, int cr, int l, int r) {
        push(idx);
        if (l <= cl && cr <= r) return st[idx];
        int cm = (cl + cr) >> 1;
        if (r <= cm) return query(idx << 1, cl, cm, l, r);
        if (l >= cm) return query(idx << 1 | 1, cm, cr, l, r);
        return f(query(idx << 1, cl, cm, l, r), query(idx << 1 | 1, cm, cr, l, r));
    }

    void update(int idx, int cl, int cr, int l, int r, const mp_t& mp) {
        push(idx);
        if (l <= cl && cr <= r) {
            lazy[idx] = combine(mp, lazy[idx]);
            push(idx);
            return;
        }
        int cm = (cl + cr) >> 1;
        if (r <= cm) update(idx << 1, cl, cm, l, r, mp), push(idx << 1 | 1);
        else if (l >= cm) update(idx << 1 | 1, cm, cr, l, r, mp), push(idx << 1);
        else update(idx << 1, cl, cm, l, r, mp), update(idx << 1 | 1, cm, cr, l, r, mp);
        st[idx] = f(st[idx << 1], st[idx << 1 | 1]);
    }

    public:
    segment_tree() : segment_tree(0) {}

    // Note: hasn't been tested yet
    explicit segment_tree(const int _n, const T &e = 0) : segment_tree(std::vector<T>(_n, e)) {}

    explicit segment_tree(const std::vector<T> &a) : n(a.size()), st((n << 2) + 2), lazy((n << 2) + 2, id()) { if (n > 0) build(1, 0, n, a); }

    T query(int l, int r) { return query(1, 0, n, l, r); }

    // Note: hasn't been tested yet
    T query(int idx) { return query(1, 0, n, idx, idx + 1); }

    void update(int l, int r, const mp_t &mp) { update(1, 0, n, l, r, mp); }

    // Note: hasn't been tested yet
    void update(int idx, const mp_t &mp) { update(1, 0, n, idx, idx + 1, mp); }

    // Note: hasn't been tested yet
    int size() const { return n; }
};

template<typename T> constexpr T _st_add(const T& a, const T &b) { return a + b; }
template<typename T> constexpr T _st_min(const T& a, const T &b) { return (b < a) ? b : a; }
template<typename T> constexpr T _st_max(const T& a, const T &b) { return (a < b) ? b : a; }
template<typename T> constexpr T _st_zero() { return 0; }

// Segment tree with `query = max` and `update = +`.
// Note: hasn't been tested yet
template<typename T> using max_segment_tree = segment_tree<T, _st_max<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> >;

// Segment tree with `query = min` and `update = +`.
// Note: hasn't been tested yet
template<typename T> using min_segment_tree = segment_tree<T, _st_min<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> >;

#endif // DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP