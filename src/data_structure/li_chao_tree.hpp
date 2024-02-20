#pragma once

#include <vector>

template<typename T>
struct linear_function {
    using input_type = T;
    T a, b;
    T operator()(T x) { return a * x + b; }
};

template<typename F, typename T = typename F::input_type, int sgn = -1>
class static_li_chao_tree {
    public:
    using function_type = F;
    using input_type = T;

    static_li_chao_tree() {}

    static_li_chao_tree(const std::vector<T> &_pos, const F &f) 
     : n(1 << (__lg(_pos.empty() ? 1 : _pos.size()) + 1)), pos(n << 1), st(n << 1, f) {
        if (_pos.empty()) return;
        std::copy(_pos.begin(), _pos.end(), pos.begin());
        std::fill(pos.begin() + static_cast<int>(_pos.size()), pos.end(), _pos.back());
    }

    void insert(const F &f) {
        insert(1, 0, n, 0, n, f);
    }

    void insert(T l, T r, const F &f) {
        insert(1, 0, n, std::lower_bound(pos.begin(), pos.end(), l) - pos.begin(), std::upper_bound(pos.begin(), pos.end(), r) - pos.begin(), f);
    }

    T query(T x) {
        int idx = std::lower_bound(pos.begin(), pos.end(), x) - pos.begin() + n;
        T ans = st[idx](x);
        for (idx >>= 1; idx > 0; idx >>= 1) 
            if constexpr (sgn == -1) ans = std::min(ans, st[idx](x));
            else ans = std::max(ans, st[idx](x));
        return ans;
    }

    private:

    void insert(int idx, int cl, int cr, int l, int r, F f) {
        if (cr <= l || cl >= r) return;
        int cm = (cl + cr) >> 1;
        if (l <= cl && cr <= r) {
            bool l_cmp, m_cmp;
            if constexpr (sgn == -1) 
                l_cmp = f(pos[cl]) < st[idx](pos[cl]),
                m_cmp = f(pos[cm]) < st[idx](pos[cm]);
            else 
                l_cmp = f(pos[cl]) > st[idx](pos[cl]),
                m_cmp = f(pos[cm]) > st[idx](pos[cm]);

            if (m_cmp) std::swap(f, st[idx]);

            if (cl + 1 == cr) return;
            if (l_cmp != m_cmp) insert(idx << 1, cl, cm, l, r, f);
            else                insert(idx << 1 | 1, cm, cr, l, r, f);
        } else insert(idx << 1, cl, cm, l, r, f),
               insert(idx << 1 | 1, cm, cr, l, r, f);
    }

    int len, n;
    std::vector<T> pos;
    std::vector<F> st;
};