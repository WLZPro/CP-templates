// https://judge.yosupo.jp/submission/168502

#ifndef DATA_STRUCTURES_SPARSE_TABLE_HPP
#define DATA_STRUCTURES_SPARSE_TABLE_HPP 1

#include <vector>
#include <functional>

// https://cp-algorithms.com/data_structures/sparse-table.html
template<typename T, auto f>
class sparse_table {
    private:
    int n;
    std::vector< std::vector<T> > st;
    std::vector<int> lg;    

    public:
    sparse_table() {}

    explicit sparse_table(const std::vector<T> &a) : n(static_cast<int>(a.size())), lg(n + 1) {
        lg[1] = 0;
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        
        st.resize(lg[n] + 1);
        st[0].assign(a.begin(), a.end());

        for (int k = 1, len = 2; k <= lg[n]; k++, len <<= 1) {
            st[k].resize(n - len + 1);
            for (int i = 0; i <= n - len; i++) st[k][i] = f(st[k - 1][i], st[k - 1][i + (len >> 1)]);
        }
    }

    explicit sparse_table(const int &_n) : sparse_table(std::vector<T>(_n)) {}

    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return f(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

#endif // DATA_STRUCTURES_SPARSE_TABLE_HPP