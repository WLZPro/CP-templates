#pragma once

#include <vector>

template<typename T>
class poly_base : public std::vector<T> {
    public:
    using std::vector<T>::vector;

    inline poly_base operator+() { return *this; }
    inline poly_base operator-() {
        poly_base ans(*this);
        for (int i = 0; i < this->size(); ++i) ans[i] = -ans[i];
        return ans;
    }

    inline poly_base &operator+=(const poly_base &rhs) {
        int n = this->size(), m = rhs.size();
        if (n < m) this->resize(m);
        for (int i = 0; i < m; ++i) this->operator[](i) += rhs[i];
        return *this;
    }

    inline friend poly_base &operator+(poly_base lhs, const poly_base &rhs) {
        return lhs += rhs;
    }

    inline poly_base &operator-=(const poly_base &rhs) {
        int n = this->size(), m = rhs.size();
        if (n < m) this->resize(m);
        for (int i = 0; i < m; ++i) this->operator[](i) -= rhs[i];
        return *this;
    }

    inline friend poly_base &operator-(poly_base lhs, const poly_base &rhs) {
        return lhs -= rhs;
    }

    inline T operator()(const T &x) const {
        T ans;
        for (std::size_t i = 0; i < this->size(); ++i) ans = ans*x + this->operator[](i);
        return ans;
    }
};

template<typename T>
class polynomial : public poly_base<T> {
    public:
    using poly_base<T>::poly_base;
};

template<typename T>
using poly = polynomial<T>;