#ifndef POLYNOMIAL_INV_HPP
#define POLYNOMIAL_INV_HPP 1

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

#endif // POLYNOMIAL_INV_HPP