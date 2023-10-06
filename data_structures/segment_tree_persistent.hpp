#include <vector>
#include <functional>
#include <numeric>

template<typename T> constexpr T my_add(T a, T b) { return a + b; }

template<typename T, auto f = my_add<T> >
class persistent_segment_tree {
    static_assert(std::is_convertible_v<decltype(f), std::function<T(T, T)> >);

    private:
    size_t n;
    unsigned int root;
    std::vector<T> st;
    std::vector<unsigned int> lc, rc;

    unsigned int build(unsigned int cl, unsigned int cr, const std::vector<T> &a) {
        if (cl + 1 == cr) {
            st.push_back(a[cl]); lc.push_back(0); rc.push_back(0);
            return st.size() - 1;
        }
        unsigned int cm = (cl + cr) >> 1;
        unsigned int tmp_l = build(cl, cm, a), tmp_r = build(cm, cr, a);
        lc.push_back(tmp_l); rc.push_back(tmp_r);
        st.push_back(f(st[tmp_l], st[tmp_r]));
        return st.size() - 1;
    }

    T query(unsigned int idx, unsigned int cl, unsigned int cr, unsigned int l, unsigned int r) const {
        if (l <= cl && cr <= r) return st[idx];
        unsigned int cm = (cl + cr) >> 1;
        if (r <= cm) return query(lc[idx], cl, cm, l, r);
        if (l >= cm) return query(rc[idx], cm, cr, l, r);
        return f(query(lc[idx], cl, cm, l, r), query(rc[idx], cm, cr, l, r));
    }

    unsigned int update(unsigned int idx, unsigned int cl, unsigned int cr, unsigned int pos, const T &val) {
        if (cl + 1 == cr) {
            st.push_back(val); lc.push_back(0); rc.push_back(0);
            return st.size() - 1;
        }
        unsigned int cm = (cl + cr) >> 1;
        unsigned int tmp_l = lc[idx], tmp_r = rc[idx];
        if (pos < cm) tmp_l = update(lc[idx], cl, cm, pos, val);
        else tmp_r = update(rc[idx], cm, cr, pos, val);
        lc.push_back(tmp_l); rc.push_back(tmp_r);
        st.push_back(f(st[tmp_l], st[tmp_r]));
        return st.size() - 1;
    }

    public:
    // Note: hasn't been tested yet
    persistent_segment_tree() : n(0) {}
    
    explicit persistent_segment_tree(const std::vector<T> &a) : n(a.size()) { root = build(0, n, a); }

    // Note: hasn't been tested yet
    explicit persistent_segment_tree(size_t _n) : persistent_segment_tree(std::vector<T>(_n)) {}

    persistent_segment_tree(size_t _n, const T &x) : persistent_segment_tree(std::vector<T>(_n, x)) {}

    unsigned int original_root() const { return root; }

    T query(unsigned int idx, unsigned int l, unsigned int r) const { return query(idx, 0, n, l, r); }

    // Note: hasn't been tested yet
    T query(unsigned int idx, unsigned int l) const { return query(idx, l, l + 1); }

    unsigned int update(unsigned int idx, unsigned int pos, const T &val) { return update(idx, 0, n, pos, val); }

    // Note: hasn't been tested yet
    size_t size() const { return n; }
};