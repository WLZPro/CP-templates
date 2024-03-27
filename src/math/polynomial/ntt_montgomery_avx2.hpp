#pragma once

#include "math/montgomery_32_avx2.hpp"

namespace ntt_avx2 {

namespace ntt_info {

template<uint32_t md> constexpr int log_ord = __builtin_ctz(md - 1);

template<uint32_t md> constexpr uint32_t w_mx;
template<> constexpr uint32_t w_mx<998244353u> = 31u;

template<uint32_t md>
constexpr montgomery_32_avx2 mm(md);

template<uint32_t md>
struct ntt_precalc_t {
    uint32_t w_m[2][log_ord<md> - 1], inv_pw_m[log_ord<md> + 1];

    constexpr ntt_precalc_t() : w_m{}, inv_pw_m{} {
        uint32_t r[2][log_ord<md> - 1];
        r[0][log_ord<md> - 2] = mm<md>.convert(w_mx<md>);
        auto inv = [](auto &&self, uint32_t a) -> uint32_t {
            return a <= 1 ? a
                 : md - static_cast<uint64_t>(md / a) * self(self, md % a) % md;
        };
        r[1][log_ord<md> - 2] = mm<md>.convert(inv(inv, w_mx<md>));

        for (int i = 0; i < 2; ++i)
            for (int k = log_ord<md> - 3; k >= 0; --k)
                r[i][k] = mm<md>.mul(r[i][k + 1], r[i][k + 1]);

        for (int i = 0; i < 2; ++i) {
            uint32_t cur = mm<md>.convert(1u);
            for (int k = 0; k < log_ord<md> - 1; ++k) 
                w_m[i][k] = mm<md>.mul(cur, r[i][k]),
                cur = mm<md>.mul(cur, r[!i][k]);
        }
        
        uint32_t inv_2_m = mm<md>.convert((md + 1) >> 1);
        inv_pw_m[0] = mm<md>.convert(1u);
        for (int k = 1; k <= log_ord<md>; ++k) 
            inv_pw_m[k] = mm<md>.mul(inv_pw_m[k - 1], inv_2_m);
    }
};

#if __cplusplus >= 202002L
template<uint32_t md>
constexpr ntt_precalc_t<md> ntt_precalc = ntt_precalc_t<md>();
#else
template<uint32_t md>
const ntt_precalc_t<md> ntt_precalc = ntt_precalc_t<md>();
#endif

}; // namespace ntt_info

// https://judge.yosupo.jp/submission/196450
// Loads/stores are unaligned
// Assumptions: `k >= 4`, `a[0..2^k)` is a valid range
template<uint32_t md, bool invert> __attribute__((target("avx2")))
void ntt_montgomery(uint32_t *a, int k) {
    using namespace ntt_info;
    const __m256i mask_2md = _mm256_set1_epi32(2 * md);
    for (int l = 0; l < k; ++l) {
        const int h = invert ? k - l - 1 : l;
        const int d = 1 << (k - h - 1);
        uint32_t w = mm<md>.convert(1u);
        for (int s = 0; s < (1 << h); ++s) {
            if (d < 8)
                for (int i = s << (k - h); i < (s << (k - h)) + d; ++i) {
                    if constexpr (invert) {
                        uint32_t z = a[i] >= a[i + d] ? a[i] - a[i + d] : a[i] + 2 * md - a[i + d];
                        uint32_t y = mm<md>.mul(z, w);
                        if ((a[i] += a[i + d]) >= 2 * md) a[i] -= 2 * md;
                        a[i + d] = y;
                    } else {
                        uint32_t y = mm<md>.mul(a[i + d], w);
                        a[i + d] = a[i];
                        if ((a[i] += y) >= 2 * md) a[i] -= 2 * md;
                        if (a[i + d] < y) a[i + d] += 2 * md;
                        a[i + d] -= y;
                    }
                }
            else {
                const __m256i wv = _mm256_set1_epi32(w);
                for (int i = s << (k - h); i < (s << (k - h)) + d; i += 8) {
                    __m256i av = _mm256_loadu_si256((__m256i*) &a[i]);
                    __m256i bv = _mm256_loadu_si256((__m256i*) &a[i + d]);
                    if constexpr (invert) {
                        __m256i z = _mm256_sub_epi32(av, bv);
                        __m256i cmpz = _mm256_cmpgt_epi32(_mm256_setzero_si256(), z);
                        z = _mm256_add_epi32(z, _mm256_and_si256(cmpz, mask_2md));
                        av = _mm256_sub_epi32(av, mask_2md);
                        av = _mm256_add_epi32(av, bv);
                        __m256i cmpa = _mm256_cmpgt_epi32(_mm256_setzero_si256(), av);
                        av = _mm256_add_epi32(av, _mm256_and_si256(cmpa, mask_2md));
                        bv = mm<md>.mul_simd(z, wv);
                    } else {
                        __m256i u = av, v = mm<md>.mul_simd(bv, wv);
                        av = _mm256_sub_epi32(u, mask_2md);
                        av = _mm256_add_epi32(av, v);
                        __m256i cmpa = _mm256_cmpgt_epi32(_mm256_setzero_si256(), av);
                        av = _mm256_add_epi32(av, _mm256_and_si256(cmpa, mask_2md));
                        __m256i cmpb = _mm256_cmpgt_epi32(v, u);
                        bv = _mm256_add_epi32(u, _mm256_and_si256(cmpb, mask_2md));
                        bv = _mm256_sub_epi32(bv, v);
                    }
                    _mm256_storeu_si256((__m256i*) &a[i], av);
                    _mm256_storeu_si256((__m256i*) &a[i + d], bv);
                }
            }
            w = mm<md>.mul(w, ntt_precalc<md>.w_m[invert][__builtin_ctz(~s)]);
        }
    }
    if constexpr (invert)
        for (int i = 0; i < (1 << k); ++i) a[i] = mm<md>.mul(a[i], ntt_precalc<md>.inv_pw_m[k]);
}

template<uint32_t md> __attribute__((target("avx2")))
inline void conv_montgomery(uint32_t *a, uint32_t *b, int k) {
    ntt_montgomery<md, false>(a, k); ntt_montgomery<md, false>(b, k);
    for (int i = 0; i < (1 << k); i += 8) {
        __m256i av = _mm256_loadu_si256((__m256i*) &a[i]);
        __m256i bv = _mm256_loadu_si256((__m256i*) &b[i]);
        av = ntt_info::mm<md>.mul_simd(av, bv);
        _mm256_storeu_si256((__m256i*) &a[i], av);
    }
    ntt_montgomery<md, true>(a, k);
}

template<uint32_t md> __attribute__((target("avx2")))
inline void conv_via_montgomery(uint32_t *a, uint32_t *b, int k) {
    using namespace ntt_info;
    for (int i = 0; i < (1 << k); ++i)
        a[i] = mm<md>.convert(a[i]),
        b[i] = mm<md>.convert(b[i]);
    conv_montgomery<md>(a, b, k);
    for (int i = 0; i < (1 << k); ++i)
        a[i] = mm<md>.val(a[i]);
}

}; // namespace ntt