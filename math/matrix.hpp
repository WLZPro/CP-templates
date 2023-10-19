#ifndef MATH_MATRIX_HPP
#define MATH_MATRIX_HPP 1

#include <vector>

template<typename T>
class matrix {
    private:
    int n, m, len;
    T *mat;

    public:
    matrix() : n(0), m(0) {}
    matrix(int _n, int _m, const T& x = 0) : n(_n), m(_m), len(n * m) { mat = new T[len]; } 

    matrix(std::vector< std::vector<T> > &_mat) : n(_mat.size()) {
        if (n > 0) m = _mat[0].size();
        len = n * m; mat = new T[len];
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) mat[i * m + j] = _mat[i][j];
    }

    int rows() const { return n; }
    int cols() const { return m; }

    T &at(int i, int j) { return mat[i * m + j]; }

    // @note Hasn't been tested yet.
    inline matrix &operator+=(const matrix &rhs) {
        for (int i = 0; i < len; i++) mat[i] += rhs.mat[i];
        return *this;
    }

    inline matrix &operator*=(const matrix &rhs) {
        int p = rhs.m, new_len = n * p;
        T *new_mat = new T[new_len];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < p; k++)
                    new_mat[i * p + k] += mat[i * m + j] * rhs.mat[j * p + k];
        std::swap(len, new_len); std::swap(m, p); std::swap(mat, new_mat);
        return *this;
    }

    static inline matrix id(int n) {
        matrix ans(n, n);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ans.at(i, j) = (i == j);
        return ans;
    }
};

template<typename T>
inline matrix<T> operator+(const matrix<T> &lhs, const matrix<T> &rhs) { matrix<T> tmp = lhs; tmp += rhs; return tmp; }

template<typename T>
inline matrix<T> operator*(const matrix<T> &lhs, const matrix<T> &rhs) { matrix<T> tmp = lhs; tmp *= rhs; return tmp; }

template<typename T, typename S>
inline matrix<T> pow(const matrix<T> &_a, const S &_b) {
    matrix<T> a = _a, ans = matrix<T>::id(a.rows());
    S b(_b);
    while (b > 0) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

#endif // MATH_MATRIX_HPP