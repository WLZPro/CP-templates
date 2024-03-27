#pragma once

#include <immintrin.h>

#include "math/montgomery_multiplication.hpp"

class montgomery_32_avx2 : public montgomery_multiplication_32 {
    public:
    using montgomery_multiplication_32::montgomery_multiplication;

    // ~47 CPU cycles
    __attribute__((target("avx2")))
    inline __m256i mul_simd(__m256i a, __m256i b) const {
        const __m256i md_vec = _mm256_set1_epi32(md);
        __m256i al = _mm256_shuffle_epi32(a, 0b00100000); // 1
        __m256i ar = _mm256_shuffle_epi32(a, 0b00110001); // 1
        __m256i bl = _mm256_shuffle_epi32(b, 0b00100000); // 1
        __m256i br = _mm256_shuffle_epi32(b, 0b00110001); // 1
        __m256i cl = _mm256_mul_epu32(al, bl); // 5
        __m256i cr = _mm256_mul_epu32(ar, br); // 5
        __m256i c = _mm256_blend_epi32(cl, _mm256_slli_si256(cr, 4), 0b10101010); // 1+1
        c = _mm256_mullo_epi32(c, _mm256_set1_epi32(r)); // 10
        const __m256i msk = _mm256_setr_epi32(-1, 0, -1, 0, -1, 0, -1, 0);
        __m256i dl = _mm256_and_si256(c, msk); // 1
        __m256i dr = _mm256_and_si256(_mm256_srli_si256(c, 4), msk); // 1+1
        dl = _mm256_mul_epu32(dl, md_vec); // 5
        dr = _mm256_mul_epu32(dr, md_vec); // 5
        cl = _mm256_add_epi64(cl, dl); // 1
        cr = _mm256_add_epi64(cr, dr); // 1
        cl = _mm256_srli_epi64(cl, 32); // 1
        cr = _mm256_srli_epi64(cr, 32); // 1
        return _mm256_blend_epi32(cl, _mm256_slli_si256(cr, 4), 0b10101010); // 1+1
    }
};