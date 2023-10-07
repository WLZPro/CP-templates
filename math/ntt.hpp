#ifndef MATH_NTT_HPP
#define MATH_NTT_HPP 1

#include "modint.hpp"

#include <bits/stdc++.h>
using namespace std;

using mint = mint998244353;

const mint w_mx = 15311432;
const mint w_mx_inv = 469870224;

vector<mint> ntt(const vector<mint> &_a, bool invert = false) {
    vector<mint> a = _a;
    int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1, j = 0; i < n; i++) {
        int k = n >> 1;
        for (; j & k; k >>= 1) j ^= k;
        j ^= k;
        if (i < j) swap(a[i], a[j]);
    }
    for (int k = 1; (1 << k) <= n; k++) {
        mint w_2_k = invert ? w_mx_inv : w_mx;
        w_2_k = pow(w_2_k, pow(mint(2, true), 23 - k).val());
        for (int i = 0; i < n; i += (1 << k)) {
        mint w = 1;
            for (int j = 0; j < (1 << (k - 1)); j++) {
                mint u = a[i + j], v = w * a[i + j + (1 << (k - 1))];
                a[i + j] = u + v;
                a[i + j + (1 << (k - 1))] = u - v;
                w *= w_2_k;
            }
        }
    }
    if (invert) {
        for (auto &x : a) x /= n;
    }
    return a;
}

vector<mint> poly_mul(const vector<mint> &_a, const vector<mint> &_b) {
    vector<mint> a = _a, b = _b;
    while ((int) a.size() < (int) b.size()) a.push_back(0);
    while ((int) b.size() < (int) a.size()) b.push_back(0);
    while (((int) a.size()) & ((int) a.size() - 1)) a.push_back(0);
    while (((int) b.size()) & ((int) b.size() - 1)) b.push_back(0);
    int n = (int) a.size();
    for (int i = 0; i < n; i++) a.push_back(0), b.push_back(0);
    a = ntt(a); b = ntt(b);
    vector<mint> c(2 * n);
    for (int i = 0; i < 2 * n; i++) c[i] = a[i] * b[i];
    return ntt(c, true);
}

#endif // MATH_NTT_HPP