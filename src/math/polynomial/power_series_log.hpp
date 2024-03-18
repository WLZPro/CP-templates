#pragma once

#include "math/polynomial/power_series_inv.hpp"

template<uint32_t md>
void log_montgomery(uint32_t *a, uint32_t *b, uint32_t *c, int k) {
    using namespace ntt;
    using namespace ntt_info;
    inv_montgomery<md>(a, b, c, k);

    static constexpr uint32_t one = mm<md>.convert(1u);
    uint32_t cur = one;
    for (int i = 0; i < (1 << k) - 1; ++i) {
        a[i] = mm<md>.mul(cur, a[i + 1]);

        cur += one;
        cur = cur >= 2 * md ? cur - 2 * md : cur;
    }
    a[(1 << k) - 1] = 0u;

    conv_montgomery<md>(b, a, k + 1);
    memset(b + (1 << k), 0, sizeof(uint32_t) << k);
}

template<uint32_t md>
void log_via_montgomery(uint32_t *a, uint32_t *b, uint32_t *c, int k) {
    using namespace ntt::ntt_info;
    for (int i = 0; i < (1 << k); ++i) a[i] = mm<md>.convert(a[i]);
    log_montgomery<md>(a, b, c, k);

    static constexpr uint32_t one = mm<md>.convert(1u);
    uint32_t cur = mm<md>.convert((1 << k) - 1);
    for (int i = (1 << k) - 1; i; --i) {
        b[i] = mm<md>.mul(b[i - 1], mm<md>.pow(cur, md - 2));
        b[i] = mm<md>.val(b[i]);
        cur = cur >= one ? cur - one : cur + 2 * md - one;
    }
    b[0] = 0u;
}