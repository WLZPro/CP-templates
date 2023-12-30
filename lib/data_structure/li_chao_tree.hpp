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
        : n(1 << ((sizeof(int) << 3) - __builtin_clz(_pos.size()))), st(n << 1, f) {
        pos.resize(n << 1);
        std::copy(_pos.begin(), _pos.end(), pos.begin());
        std::fill(pos.begin() + static_cast<int>(_pos.size()), pos.end(), _pos.back());
    }

    void insert(const F &f) { insert(1, 0, n, f); }

    T query(T x) {
        int idx = std::lower_bound(pos.begin(), pos.end(), x) - pos.begin() + n;
        T ans = st[idx](x);
        for (idx >>= 1; idx > 0; idx >>= 1) ans = std::min(ans, st[idx](x));
        return ans;
    }

    private:
    void insert(int idx, int l, int r, F f) {
        int m = (l + r) >> 1;

        bool l_cmp, m_cmp;
        if constexpr (sgn == -1) 
            l_cmp = f(pos[l]) < st[idx](pos[l]),
            m_cmp = f(pos[m]) < st[idx](pos[m]);
        else 
            l_cmp = f(pos[l]) > st[idx](pos[l]),
            m_cmp = f(pos[m]) > st[idx](pos[m]);

        if (m_cmp) std::swap(f, st[idx]);

        if (l + 1 == r) return;
        if (l_cmp != m_cmp) insert(idx << 1, l, m, f);
        else                insert(idx << 1 | 1, m, r, f);
    }

    int len, n;
    std::vector<T> pos;
    std::vector<F> st;
};