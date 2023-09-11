#include <vector>

/**
 * @brief Sparse table implementation.
 * Supports static RMQ with O(n log n) precomputation time, O(n log n) memory, and O(1) queries.
 * 
 * @tparam T Value type
 * @tparam T&(*f)(const T &, const T &) Combiner function (usually std::min/std::max)
 */
template<typename T, const T&(*f)(const T&, const T&)>
class sparse_table {
    private:
    unsigned int n;
    std::vector< std::vector<T> > st;
    std::vector<unsigned int> lg;    

    public:
    sparse_table() {}
        
    sparse_table(const std::vector<T> &a) {
        n = a.size();
        lg.resize(n + 1); lg[1] = 0;
        for (unsigned int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        
        st.resize(lg[n] + 1);
        st[0].assign(a.begin(), a.end());

        for (unsigned int k = 1, len = 2; k <= lg[n]; k++, len <<= 1) {
            st[k].resize(n - len + 1);
            for (unsigned int i = 0; i <= n - len; i++) st[k][i] = f(st[k - 1][i], st[k - 1][i + (len >> 1)]);
        }
    }

    sparse_table(const unsigned int &_n) : n(_n) {
        sparse_table(std::vector<T>(n, 0));
    }

    /**
     * @brief Range minimum/maximum query on interval [l, r)
     * 
     * @param l Left endpoint (included)
     * @param r Right endpoint (excluded)
     * @return const T& f(a[l], ..., a[r - 1])
     */
    const T &query(unsigned int l, unsigned int r) const {
        unsigned int k = lg[r - l];
        return f(st[k][l], st[k][r - (1 << k)]);
    }
};