#ifndef DATA_STRUCTURES_SEGMENT_TREE_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_HPP 1

#include <vector>
#include <functional>
#include <string>

// https://codeforces.com/blog/entry/18051
template<typename T, auto f>
class segment_tree {
    private:
    int n;
    std::vector<T> st;
    #ifdef DEBUG
    std::vector<T> debug;
    #endif
    
    public:
    segment_tree() {}

    explicit segment_tree(const std::vector<T> &a) : n(static_cast<int>(a.size())), st(n << 1) {
        for (int i = 0; i < n; i++) st[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) st[i] = f(st[i << 1], st[i << 1 | 1]);
        #ifdef DEBUG
        debug = a;
        #endif
    }

    // @note Hasn't been tested yet.
    explicit segment_tree(const int &_n, const T &e = 0) : segment_tree(std::vector<T>(_n, e)) {}

    // @note Hasn't been tested yet.
    template<typename TBegin, typename TEnd>
    segment_tree(const TBegin &b, const TEnd &e) : segment_tree(std::vector<T>(b, e)) {}

    void update(int idx, const T &new_val) {
        #ifdef DEBUG
        debug[idx] = new_val;
        #endif
        for (st[idx += n] = new_val; idx >>= 1; ) st[idx] = f(st[idx << 1], st[idx << 1 | 1]);
    }

    // @note Hasn't been tested yet.
    const T &query_all() const { return st[1]; }

    const T &query(int idx) const { return st[idx + n]; }

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

    // @note Hasn't been tested yet.
    const T &operator[](int idx) const { return st[idx + n]; }

    // @note Hasn't been tested yet.
    const int &size() const { return n; }

    inline friend std::string to_string(const segment_tree &st) {
        #ifdef DEBUG
        return to_string(st.debug);
        #else
        return "";
        #endif
    }
};

#endif // DATA_STRUCTURES_SEGMENT_TREE_HPP