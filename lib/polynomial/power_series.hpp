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

// https://homepages.loria.fr/PZimmermann/papers/fastnewton.ps.gz
template<typename T>
inline poly<T> exp(const poly<T> &_a, int n) {
    const int sz = 1 << ((sizeof(int) << 3) - __builtin_clz(n));
    const poly<T> one = poly<T>::constant(1), two = poly<T>::constant(2);
    poly<T> f = {1}, g = {1}; int m = 1;
    poly<T> _q = deriv(_a), q; q.reserve(sz);
    poly<T> a; a.reserve(sz);
    int q_i = 0, a_i = 0;
    while ((m << 1) <= sz) {
        g *= two - f * g; g.truncate_to(m);
        for (; q_i < std::min(static_cast<int>(_q.size()), m - 1); q_i++) q.push_back(_q[q_i]);
        poly<T> w = q + g * (deriv(f) - f * q); w.truncate_to((m << 1) - 1);
        for (; a_i < std::min(static_cast<int>(_a.size()), m << 1); a_i++) a.push_back(_a[a_i]);
        f *= one + a - integr(w); f.truncate_to(m << 1);
        m <<= 1;
    }
    f.truncate_to(n);
    return f;
}

template<typename T>
inline poly<T> exp(const poly<T> &a) { return exp(a, static_cast<int>(a.size())); }

#endif // POLYNOMIAL_POWER_SERIES_HPP