#include <vector>
#include <functional>

template<typename T, auto f>
class segment_tree {

    static_assert(std::is_convertible_v<decltype(f), std::function<T(T, T)> >);

    private:
    unsigned int n;
    std::vector<T> st;
    
    public:
    segment_tree() {}

    explicit segment_tree(const std::vector<T> &a) : n(a.size()), st(n << 1) {
        for (unsigned int i = 0; i < n; i++) st[i + n] = a[i];
        for (unsigned int i = n - 1; i > 0; i--) {
            st[i] = f(st[i << 1], st[i << 1 | 1]);
        }
    }

    explicit segment_tree(unsigned int _n) : n(_n), st(n << 1) {}

    void update(unsigned int idx, const T &new_val) {
        for (st[idx += n] = new_val; idx >>= 1; ) st[idx] = f(st[idx << 1], st[idx << 1 | 1]);
    }

    T query(unsigned int l) const { return st[l + n]; }

    T query(unsigned int l, unsigned int r) const {
        T ans_l, ans_r;
        bool l_def = false, r_def = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
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