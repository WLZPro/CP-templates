#ifndef MATH_MATRIX_HPP
#define MATH_MATRIX_HPP 1

#include <vector>

template<typename T>
class matrix {
    private:
    int n, m, len;
    std::vector<T> mat;

    public:
    matrix() : n(0), m(0) {}
    matrix(int _n, int _m, const T& x = 0) : n(_n), m(_m), len(n * m), mat(len, x) {} 

    matrix(std::vector< std::vector<T> > &_mat) : n(_mat.size()) {
        if (n > 0) m = _mat[0].size();
        len = n * m; mat.resize(len);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) mat[i * m + j] = _mat[i][j];
    }

    constexpr int rows() const { return n; }
    constexpr int cols() const { return m; }

    T &at(int i, int j) { return mat[i * m + j]; }

    // @note Hasn't been tested yet.
    inline matrix &operator+=(const matrix &rhs) {
        for (int i = 0; i < len; i++) mat[i] += rhs.mat[i];
        return *this;
    }

    // @note Hasn't been tested yet.
    inline friend matrix operator+(matrix lhs, const matrix &rhs) { return lhs += rhs; }

    // @note Hasn't been tested yet.
    inline matrix &operator-=(const matrix &rhs) {
        for (int i = 0; i < len; i++) mat[i] -= rhs.mat[i];
        return *this;
    }

    // @note Hasn't been tested yet.
    inline friend matrix operator-(matrix lhs, const matrix &rhs) { return lhs -= rhs; }

    inline matrix &operator*=(const matrix &rhs) {
        int p = rhs.m, new_len = n * p;
        std::vector<T> new_mat(new_len);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < p; k++)
                    new_mat[i * p + k] += mat[i * m + j] * rhs.mat[j * p + k];
        std::swap(len, new_len); std::swap(m, p); std::swap(mat, new_mat);
        return *this;
    }

    inline friend matrix operator*(matrix lhs, const matrix &rhs) { return lhs *= rhs; }

    // @note Hasn't been tested yet.
    static inline matrix id(int n) {
        matrix ans(n, n, 0);
        for (int i = 0; i < n * n; i += n + 1) ans.mat[i] = 1;
        return ans;
    }

    template<typename TExp>
    inline friend matrix pow(const matrix &_a, const TExp &_b) {
        matrix<T> a(_a), ans = matrix<T>::id(a.rows());
        TExp b(_b);
        while (b > 0) {
            if (b & 1) ans *= a;
            a *= a;
            b >>= 1;
        }
        return ans;
    }

    inline friend std::string to_string(const matrix &a) {
        using namespace std;
        std::vector< std::vector<T> > mat(a.rows(), std::vector<T>(a.cols()));
        for (int i = 0; i < a.rows(); i++) for (int j = 0; j < a.cols(); j++) mat[i][j] = a.mat[i * a.cols() + j];
        return to_string(mat);
    }
};

#endif // MATH_MATRIX_HPP