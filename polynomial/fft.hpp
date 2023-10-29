#ifndef POLYNOMIAL_FFT_HPP
#define POLYNOMIAL_FFT_HPP 1

#include "math/modint.hpp"
#include "polynomial/polynomial.hpp"

#include <complex>
#include <vector>
#include <numbers>

template<typename T>
T fft_root(int, bool);

template<>
modint998244353 fft_root(int k, bool invert) {   
    modint998244353 ans = invert ? 469870224 : 15311432;
    for (int i = 0; i < 23 - k; i++) ans *= ans;
    return ans;
}

template<>
constexpr std::complex<long double> fft_root(int k, bool invert) {
    long double ang = 2 * std::numbers::pi / (1 << k) * (invert ? -1 : 1);
    return std::complex<long double>(std::cos(ang), std::sin(ang));
}

template<>
constexpr std::complex<double> fft_root(int k, bool invert) {
    return (std::complex<double>) fft_root< std::complex<long double> >(k, invert);
}

template<typename T>
inline void fft(std::vector<T> &a, bool invert = false) {
    int n = static_cast<int>(a.size());
    for (int i = 1, j = 0; i < n; i++) {
        int k = n >> 1;
        for (; j & k; k >>= 1) j ^= k;
        j ^= k;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int k = 1, len = 2; len <= n; k++, len <<= 1) {
        T w_2_k = fft_root<T>(k, invert);
        for (int i = 0; i < n; i += len) {
            T w = 1;
            for (int j = 0; j < (len >> 1); j++) {
                T u = a[i + j], v = w * a[i + j + (len >> 1)];
                a[i + j] = u + v; a[i + j + (len >> 1)] = u - v;
                w *= w_2_k;
            }
        }
    }
    if (invert) for (auto &x : a) x /= (T) n;
}

template<typename T>
inline poly<T> &operator*=(poly<T> &lhs, poly<T> rhs) {
    if (lhs.empty() || rhs.empty()) return lhs = {};
    int n = static_cast<int>(lhs.size()), m = static_cast<int>(rhs.size());
    int sz = 1 << ((sizeof(int) << 3) - __builtin_clz(n + m - 1));
    lhs.expand_to(sz); rhs.expand_to(sz);
    fft(lhs); fft(rhs);
    for (int i = 0; i < sz; i++) lhs[i] *= rhs[i];
    fft(lhs, true);
    lhs.truncate_to(n + m - 1);
    return lhs;
}

template<typename T>
inline poly<T> operator*(poly<T> lhs, const poly<T> &rhs) { return lhs *= rhs; }

#endif // POLYNOMIAL_FFT_HPP