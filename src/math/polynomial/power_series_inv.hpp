#pragma once

#include "math/polynomial/ntt_montgomery.hpp"

// https://cp-algorithms.com/algebra/polynomial.html#sievekingkung-algorithm
// Input: `a[0..2^k)` (in Montgomery form), output: `b[0..2^k)`, cache: `c[0..2^(k+1))`
// Assumptions: ranges `a[0..2^(k+1))`, `b[0..2^(k+1))`, `c[0..2^(k+1))`
// are valid (and disjoint), `b[i] = 0` initially
template<uint32_t md>
void inv_montgomery(uint32_t *a, uint32_t *b, uint32_t *c, int k) {
    using namespace ntt;
    using namespace ntt::ntt_info;
    b[0] = mm<md>.pow(a[0], md - 2);
    static constexpr uint32_t two = mm<md>.convert(2u);

    for (int l = 1; l <= k; ++l) {
        memcpy(c, a, sizeof(uint32_t) << l);
        ntt_montgomery<md, false>(c, l + 1);
        ntt_montgomery<md, false>(b, l + 1);
        for (int i = 0; i < (1 << (l + 1)); ++i) {
            uint32_t ab = mm<md>.mul(c[i], b[i]);
            ab = two >= ab ? two - ab : two + 2 * md - ab;
            b[i] = mm<md>.mul(b[i], ab);
        }
        ntt_montgomery<md, true>(b, l + 1);
        memset(b + (1 << l), 0, sizeof(uint32_t) << l);
    }
}

// See `inv_montgomery`
template<uint32_t md>
inline void inv_via_montgomery(uint32_t *a, uint32_t *b, uint32_t *c, int k) {
    using namespace ntt::ntt_info;
    for (int i = 0; i < (1 << k); ++i) a[i] = mm<md>.convert(a[i]);
    inv_montgomery<md>(a, b, c, k);
    for (int i = 0; i < (1 << k); ++i) b[i] = mm<md>.val(b[i]);
}