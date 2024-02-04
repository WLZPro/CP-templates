#include <iostream>
#include <vector>
#include <immintrin.h>

#include "util/abstract_types.hpp"

// https://codeforces.com/blog/entry/89399
// Assumptions: `N` is a power of 2
template<typename M, size_t N = 1 << 19>
class avx_segment_tree {
    using T = typename M::T;

    public:
    using value_type = T;

    avx_segment_tree() {}

    avx_segment_tree(const std::vector<T> &a) {
        st[0] = M::e;
        std::copy(a.begin(), a.end(), st + N);
        std::fill(st + N + a.size(), st + 2 * N, M::e);
        for (int i = N - 1; i > 0; i--) st[i] = M::op(st[i << 1], st[i << 1 | 1]);
    }

    __attribute__((target("avx2")))
    T query(int l, int r) const {
        if (l == r) return st[l + N];

        int mbit = ffs(l ^ r);
        int reset = ((1 << mbit) - 1);
        int m = r & ~reset;

        using vecint __attribute__((vector_size(32))) = T;
        __m256i identity_vec = _mm256_set1_epi32(M::e);
        vecint vec_ans = (vecint) identity_vec;
        __m256i indexes = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);

        if ((l & reset) != 0) {
            int l2 = l - 1 + N, r2 = m - 1 + N;
            int modbit = 0, maxmodbit = ffs(l2 ^ r2) + 1;
            vecint l2_vec = (vecint) _mm256_srav_epi32(_mm256_set1_epi32(l2), indexes);

    #define LOOP(content) if (modbit + 8 <= maxmodbit) { \
                vec_ans = (vecint) op((__m256i) vec_ans, _mm256_i32gather_epi32((int*) st, (__m256i) (((l2_vec & 1) - 1) & (l2_vec | 1)), 4)); \
                l2_vec >>= 8; \
                modbit += 8; \
                content \
            }
            LOOP(LOOP(LOOP(LOOP())))
    #undef LOOP

            __m256i tmp = _mm256_i32gather_epi32((int*) st, (__m256i) (((l2_vec & 1) - 1) & (l2_vec | 1)), 4);
            __m256i mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(maxmodbit & 7), indexes);
            vec_ans = (vecint) op((__m256i) vec_ans, _mm256_blendv_epi8(identity_vec, tmp, mask));
        } else vec_ans[0] = M::op(vec_ans[0], st[(l + N) >> mbit]);

        if ((r & reset) != reset) {
            int l2 = m + N, r2 = r + 1 + N;
            int modbit = 0, maxmodbit = ffs(l2 ^ r2) + 1;
            vecint r2_vec = (vecint) _mm256_srav_epi32(_mm256_set1_epi32(r2), indexes);

    #define LOOP(content) if(modbit + 8 <= maxmodbit) { \
                vec_ans = (vecint) op((__m256i) vec_ans, _mm256_i32gather_epi32((int*) st, (__m256i) (~((r2_vec & 1) - 1) & (r2_vec - 1)), 4)); \
                r2_vec >>= 8; \
                modbit += 8; \
                content \
            }
            LOOP(LOOP(LOOP(LOOP())))
    #undef LOOP

            __m256i tmp = _mm256_i32gather_epi32((int*) st, (__m256i) (~((r2_vec & 1) - 1) & (r2_vec - 1)), 4);
            __m256i mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(maxmodbit & 7), indexes);
            vec_ans = (vecint) op((__m256i) vec_ans, _mm256_blendv_epi8(identity_vec, tmp, mask));
        } else {
            vec_ans[0] = M::op(vec_ans[0], st[(r + N) >> mbit]);
        }

        __m128i low128 = _mm256_castsi256_si128((__m256i) vec_ans);
        __m128i high128 = _mm256_extractf128_si256((__m256i) vec_ans, 1);
        __m128i ans128 = op(low128, high128);
        T ans = M::e;
        for (int i = 0; i < 4; i++) {
            using V __attribute__((vector_size(16))) = T;
            ans = M::op(ans, ((V) ans128)[i]);
        }
        return ans;
    }

    private:
    T st[2 * N];

    __attribute__((target("sse4.1")))
    static __m128i op(__m128i a, __m128i b) {
        if constexpr (std::is_same_v<M, addition<T> >) return _mm_add_epi32(a, b);
        if constexpr (std::is_same_v<M, minimum<int32_t> >)  return _mm_min_epi32(a, b);
        if constexpr (std::is_same_v<M, minimum<uint32_t> >) return _mm_min_epu32(a, b);
        if constexpr (std::is_same_v<M, maximum<int32_t> >)  return _mm_max_epi32(a, b);
        if constexpr (std::is_same_v<M, maximum<uint32_t> >) return _mm_max_epu32(a, b);
    }

    __attribute__((target("avx2")))
    static __m256i op(__m256i a, __m256i b) {
        if constexpr (std::is_same_v<M, addition<T> >) return _mm256_add_epi32(a, b);
        if constexpr (std::is_same_v<M, minimum<int32_t> >)  return _mm256_min_epi32(a, b);
        if constexpr (std::is_same_v<M, minimum<uint32_t> >) return _mm256_min_epu32(a, b);
        if constexpr (std::is_same_v<M, maximum<int32_t> >)  return _mm256_max_epi32(a, b);
        if constexpr (std::is_same_v<M, maximum<uint32_t> >) return _mm256_max_epu32(a, b);
    }

    static int ffs(unsigned int x) {
        return sizeof(unsigned int) * 8 - __builtin_clz(x) - 1;
    }
};