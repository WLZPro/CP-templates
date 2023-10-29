#ifndef POLYNOMIAL_POWER_SERIES_HPP
#define POLYNOMIAL_POWER_SERIES_HPP 1

#include "polynomial/polynomial.hpp"
#include "polynomial/fft.hpp"

#include <algorithm>

// https://cp-algorithms.com/algebra/polynomial.html#sievekingkung-algorithm
template<typename T>
inline poly<T> inv(const poly<T> &_a, int n) {
    const poly<T> two = poly<T>::constant(2);
    int m = static_cast<int>(_a.size());
    poly<T> b = poly<T>::constant(((T) 1) / _a[0]);
    poly<T> a; a.reserve(m);
    for (int i = 0, len = 2; len < (n << 1); len <<= 1) {
        for (; i < std::min(len, m); i++) a.push_back(_a[i]);
        b *= two - a * b;
        b.truncate_to(len);
    }
    b.truncate_to(n);
    return b;
}

template<typename T>
inline poly<T> inv(const poly<T> &a) { return inv(a, static_cast<int>(a.size())); }

// https://cp-algorithms.com/algebra/polynomial.html#logarithm
template<typename T>
inline poly<T> log(const poly<T> &a, int n) {
    poly<T> ans = integr(deriv(a) * inv(a, n));
    ans.truncate_to(n);
    return ans;
}

template<typename T>
inline poly<T> log(const poly<T> &a) { return log(a, static_cast<int>(a.size())); }

// https://cp-algorithms.com/algebra/polynomial.html#exponent
template<typename T>
inline poly<T> exp(const poly<T> &_a, int n) {
    const poly<T> one = poly<T>::constant(1);
    int m = static_cast<int>(_a.size());
    poly<T> ans = one, a; a.reserve(m);
    for (int i = 0, len = 2; len < (n << 1); len <<= 1) {
        for (; i < std::min(m, len << 1); i++) a.push_back(_a[i]);
        ans *= (one + a - log(ans));
        ans.truncate_to(len << 1);
    }
    ans.truncate_to(n);
    return ans;
}

template<typename T>
inline poly<T> exp(const poly<T> &a) { return exp(a, static_cast<int>(a.size())); }

#endif // POLYNOMIAL_POWER_SERIES_HPP