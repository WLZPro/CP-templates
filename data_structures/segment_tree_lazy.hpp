// https://judge.yosupo.jp/submission/168738

#ifndef DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP 1

#include <vector>
#include <functional>

// https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
template<typename T, auto f, typename TMap, auto apply, auto combine, auto id>
class segment_tree {
    protected:
    int n, lg;
    std::vector<T> st;
    std::vector<TMap> lazy;

    inline void update_from_children(int idx) { st[idx] = f(st[idx << 1], st[idx << 1 | 1]); }

    inline void apply_to_node(int idx, const TMap &mp) {
        st[idx] = apply(mp, st[idx]);
        if (idx < n) lazy[idx] = combine(mp, lazy[idx]);
    }

    inline void push(int idx) {
        apply_to_node(idx << 1, lazy[idx]);
        apply_to_node(idx << 1 | 1, lazy[idx]);
        lazy[idx] = id();
    }

    public:
    // @note Hasn't been tested yet.
    segment_tree() : segment_tree(0) {}

    explicit segment_tree(const std::vector<T> &a) : n(static_cast<int>(a.size())) {
        if (a.empty()) return;
        lg = sizeof(int) * 8 - __builtin_clz(n);
        st.resize(n << 1); lazy.assign(n, id());
        for (int i = 0; i < n; i++) st[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) update_from_children(i);
    }

    // @note Hasn't been tested yet.
    explicit segment_tree(const int &_n, const T &e = 0) : segment_tree(std::vector<T>(_n, e)) {}

    template<typename TBegin, typename TEnd>
    segment_tree(const TBegin &b, const TEnd &e) : segment_tree(std::vector<T>(b, e)) {}

    void set(int idx, const T &x) {
        idx += n;
        for (int i = lg; i > 0; i--) push(idx >> i);
        st[idx] = x;
        for (int i = 1; i <= lg; i++) update_from_children(idx >> i); 
    }

    // @note Hasn't been tested yet.
    void update_all(const TMap &mp) { update(0, n - 1, mp); }

    // @note Hasn't been tested yet.
    void update(int idx, const TMap &mp) {
        idx += n;
        for (int i = lg; i > 0; i--) push(idx >> i);
        st[idx] = apply(mp, st[idx]);
        for (int i = 1; i <= lg; i++) update_from_children(idx >> i);
    }

    void update(int l, int r, const TMap &mp) {
        l += n; r += n + 1;
        for (int i = lg; i > 0; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int tmp_l = l, tmp_r = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply_to_node(l++, mp);
            if (r & 1) apply_to_node(--r, mp);
        }
        l = tmp_l; r = tmp_r;

        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) update_from_children(l >> i);
            if (((r >> i) << i) != r) update_from_children((r - 1) >> i);
        }
    }

    T query_all() const { return st[1]; }

    T query(int idx) {
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
                else ans_l = f(ans_l, st[l++]);
            }
            if (r & 1) {
                if (!r_def) ans_r = st[--r], r_def = true;
                else ans_r = f(st[--r], ans_r);
            }
        }
        if (!l_def) return ans_r;
        if (!r_def) return ans_l;
        return f(ans_l, ans_r);
    }

    // @note Hasn't been tested yet.
    T operator[](int idx) { return query(idx); }

    // @note Hasn't been tested yet.
    int size() const { return n; }
};

template<typename T> constexpr T _st_add(const T& a, const T &b) { return a + b; }
template<typename T> constexpr T _st_min(const T& a, const T &b) { return (b < a) ? b : a; }
template<typename T> constexpr T _st_max(const T& a, const T &b) { return (a < b) ? b : a; }
template<typename T> constexpr T _st_zero() { return 0; }

// @note Hasn't been tested yet.
template<typename T> using max_segment_tree = segment_tree<T, _st_max<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> >;
template<typename T> using min_segment_tree = segment_tree<T, _st_min<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> >;

#endif // DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP