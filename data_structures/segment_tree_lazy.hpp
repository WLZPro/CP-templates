// https://judge.yosupo.jp/submission/168515

#ifndef DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP 1

#include <vector>
#include <functional>

// https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
template<typename T, auto f, typename mp_t, auto apply, auto combine, auto id>
class segment_tree {
    protected:
    int n, lg;
    std::vector<T> st;
    std::vector<mp_t> lazy;

    inline void update_from_children(int idx) { st[idx] = f(st[idx << 1], st[idx << 1 | 1]); }

    inline void apply_to_node(int idx, const mp_t &mp) {
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

    // @note Hasn't been tested yet.
    explicit segment_tree(const int _n, const T &e = 0) : segment_tree(std::vector<T>(_n, e)) {}

    explicit segment_tree(const std::vector<T> &a) : n(static_cast<int>(a.size())) {
        if (a.empty()) return;
        lg = sizeof(int) * 8 - __builtin_clz(n);
        st.resize(n << 1); lazy.assign(n, id());
        for (int i = 0; i < static_cast<int>(a.size()); i++) st[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) update_from_children(i);
    }

    void set(int l, const T &x) {
        l += n;
        for (int i = lg; i > 0; i--) push(l >> i);
        st[l] = x;
        for (int i = 1; i <= lg; i++) update_from_children(l >> i); 
    }

    // @note Hasn't been tested yet.
    void update(int l, const mp_t &mp) {
        l += n;
        for (int i = lg; i > 0; i--) push(l >> i);
        st[l] = apply(mp, st[l]);
        for (int i = 1; i <= lg; i++) update_from_children(l >> i);
    }

    void update(int l, int r, const mp_t &mp) {
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

    T query() const { return st[1]; }

    T query(int l) {
        l += n;
        for (int i = lg; i > 0; i--) push(l >> i);
        return st[l];
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
    int size() const { return n; }
};

template<typename T> constexpr T _st_add(const T& a, const T &b) { return a + b; }
template<typename T> constexpr T _st_min(const T& a, const T &b) { return (b < a) ? b : a; }
template<typename T> constexpr T _st_max(const T& a, const T &b) { return (a < b) ? b : a; }
template<typename T> constexpr T _st_zero() { return 0; }

// @note Hasn't been tested yet.
template<typename T> 
class max_segment_tree : public segment_tree<T, _st_max<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> > {
    using segment_tree<T, _st_max<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> >::segment_tree;

    public:
    int lower_bound(const T& x) {
        int idx = 1;
        for (int i = 1; i <= this->lg; i++) {
            this->push(idx);
            idx <<= 1;
            if (this->st[idx] < x) idx++;
        }
        if (this->st[idx] < x) return this->n;
        return idx - this->n;
    }
};

template<typename T> using min_segment_tree = segment_tree<T, _st_min<T>, T, _st_add<T>, _st_add<T>, _st_zero<T> >;

#endif // DATA_STRUCTURES_SEGMENT_TREE_LAZY_HPP