#pragma once

#include "util/abstract_types.hpp"

#include <vector>
#include <string>

template<typename _Sg>
class sparse_table {
    using T = typename _Sg::T;

    public:
    using value_type = T;

    sparse_table() : n(0) {}

    template<typename ...Args>
    explicit sparse_table(Args &&...args) {
        std::vector<T> a(args...);

        #ifdef DEBUG
        _dbg = a;
        #endif

        n = static_cast<int>(a.size());
        st.resize((sizeof(n) << 3) - __builtin_clz(n)); st[0] = a;

        for (int k = 1, len = 2; len <= n; k++, len <<= 1) {
            st[k].resize(n - len + 1);
            for (int i = 0; i <= n - len; i++) st[k][i] = _Sg::op(st[k - 1][i], st[k - 1][i + (len >> 1)]);
        }
    }

    const T &operator[](int idx) const { return st[0][idx]; }

    T query(int l, int r) const {
        int k = (sizeof(r) << 3) - __builtin_clz(r - l + 1) - 1;
        return _Sg::op(st[k][l], st[k][r - (1 << k) + 1]);
    }

    int size() const { return n; }

    friend std::string to_string(const sparse_table &st) {
        #ifdef DEBUG
        return to_string(st._dbg);
        #else
        return "";
        #endif
    }

    private:
    int n;
    std::vector< std::vector<T> > st;

    #ifdef DEBUG
    std::vector<T> _dbg;
    #endif
};