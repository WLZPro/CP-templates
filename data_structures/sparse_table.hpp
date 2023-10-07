#ifndef DATA_STRUCTURES_SPARSE_TABLE_HPP
#define DATA_STRUCTURES_SPARSE_TABLE_HPP 1

#include <vector>
#include <functional>

template<typename T, auto f>
class sparse_table {

    static_assert(std::is_convertible_v<decltype(f), std::function<T(T, T)> >);

    private:
    unsigned int n;
    std::vector< std::vector<T> > st;
    std::vector<unsigned int> lg;    

    public:
    sparse_table() {}

    explicit sparse_table(const std::vector<T> &a) : n(a.size()), lg(n + 1) {
        lg[1] = 0;
        for (unsigned int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        
        st.resize(lg[n] + 1);
        st[0].assign(a.begin(), a.end());

        for (unsigned int k = 1, len = 2; k <= lg[n]; k++, len <<= 1) {
            st[k].resize(n - len + 1);
            for (unsigned int i = 0; i <= n - len; i++) st[k][i] = f(st[k - 1][i], st[k - 1][i + (len >> 1)]);
        }
    }

    explicit sparse_table(const unsigned int &_n) : sparse_table(std::vector<T>(_n)) {}

    T query(unsigned int l, unsigned int r) const {
        unsigned int k = lg[r - l];
        return f(st[k][l], st[k][r - (1 << k)]);
    }
};

#endif // DATA_STRUCTURES_SPARSE_TABLE_HPP