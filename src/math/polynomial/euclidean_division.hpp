#pragma once

#include <cstring>
#include <algorithm>

#include "math/polynomial/ntt_montgomery.hpp"
#include "math/polynomial/power_series_inv.hpp"

// https://cp-algorithms.com/algebra/polynomial.html#euclidean-division
// Assigns `A := A/B`, `B := reverse(B)`
// where `A = a[0..n)`, `B = b[0..m)`
//
// Assumptions:
// - `n >= m`
// - `2^k >= n-m+1`
// - `a`, `b`, `c1`, `c2` have length `2^(k+1)`
template<uint32_t md>
void div_montgomery(uint32_t *a, uint32_t *b, int n, int m, int k,
                    uint32_t *c1, uint32_t *c2) {
    using namespace ntt;
    std::reverse(a, a + n);
    std::reverse(b, b + m);
    inv_montgomery<md>(b, c1, c2, k);
    memset(a + (1 << k), 0, sizeof(uint32_t) << k);
    conv_montgomery<md>(a, c1, k + 1);
    std::reverse(a, a + (n - m + 1));
}

// See `div_montgomery`
template<uint32_t md>
void div_via_montgomery(uint32_t *a, uint32_t *b, int n, int m, int k,
                        uint32_t *c1, uint32_t *c2) {
    using namespace ntt::ntt_info;

    for (int i = 0; i < (1 << k); ++i) a[i] = mm<md>.convert(a[i]);
    for (int i = 0; i < m; ++i) b[i] = mm<md>.convert(b[i]);

    div_montgomery<md>(a, b, n, m, k, c1, c2);

    for (int i = 0; i <= n - m; ++i) a[i] = mm<md>.val(a[i]);
}

// https://cp-algorithms.com/algebra/polynomial.html#euclidean-division
// Assigns `(A, B) := (A/B, A mod B)`
// where `A = a[0..n)`, `B = b[0..m)`
//
// Assumptions:
// - `n >= m`
// - `2^k >= n-m+1`
// - `2^(k2) >= n`
// - `a`, `b`, `c1`, `c2` have length `2^(k+1)`
// - `c3` has length `n`
template<uint32_t md>
void div_mod_montgomery(uint32_t *a, uint32_t *b, int n, int m, int k, int k2,
                        uint32_t *c1, uint32_t *c2, uint32_t *c3) {
    using namespace ntt;
    memcpy(c3, a, sizeof(uint32_t) * n);
    div_montgomery<md>(a, b, n, m, k, c1, c2);
    memcpy(c1, a, sizeof(uint32_t) * (n - m + 1));
    memset(c1 + (n - m + 1), 0, sizeof(uint32_t) * ((1 << (k + 1)) - (n - m + 1)));
    std::reverse(b, b + m);
    conv_montgomery<md>(b, c1, k2);
    for (int i = 0; i < m - 1; ++i) {
        b[i] = c3[i] >= b[i] ? c3[i] - b[i] : c3[i] + 2 * md - b[i];
    }
}

// See `div_mod_montgomery`
template<uint32_t md>
void div_mod_via_montgomery(uint32_t *a, uint32_t *b, int n, int m, int k, int k2,
                            uint32_t *c1, uint32_t *c2, uint32_t *c3) {
    using namespace ntt::ntt_info;
    for (int i = 0; i < n; ++i) a[i] = mm<md>.convert(a[i]);
    for (int i = 0; i < m; ++i) b[i] = mm<md>.convert(b[i]);

    div_mod_montgomery<md>(a, b, n, m, k, k2, c1, c2, c3);

    for (int i = 0; i <= n - m; ++i) a[i] = mm<md>.val(a[i]);
    for (int i = 0; i < m - 1; ++i) b[i] = mm<md>.val(b[i]);
}