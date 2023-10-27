// Static RMQ: https://judge.yosupo.jp/submission/168572
// Static range sum: https://judge.yosupo.jp/submission/168574
// Range sum with updates: https://judge.yosupo.jp/submission/168576
// Custom operations (linear function composition): https://judge.yosupo.jp/submission/168510

#ifndef DATA_STRUCTURES_SEGMENT_TREE_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_HPP 1

#include <vector>
#include <functional>

// https://codeforces.com/blog/entry/18051
template<typename T, auto f>
class segment_tree {
    private:
    int n;
    std::vector<T> st;
    
    public:
    segment_tree() {}

    explicit segment_tree(const std::vector<T> &a) : n(static_cast<int>(a.size())), st(n << 1) {
        for (int i = 0; i < n; i++) st[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) {
            st[i] = f(st[i << 1], st[i << 1 | 1]);
        }
    }

    explicit segment_tree(int _n) : n(_n), st(n << 1) {}

    void update(int idx, const T &new_val) {
        for (st[idx += n] = new_val; idx >>= 1; ) st[idx] = f(st[idx << 1], st[idx << 1 | 1]);
    }

    T query(int l) const { return st[l + n]; }

    T query(int l, int r) const {
        T ans_l, ans_r;
        bool l_def = false, r_def = false;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
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
};

#endif // DATA_STRUCTURES_SEGMENT_TREE_HPP