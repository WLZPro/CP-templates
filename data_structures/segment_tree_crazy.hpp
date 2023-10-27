// https://judge.yosupo.jp/submission/168647

#ifndef DATA_STRUCTURES_SEGMENT_TREE_CRAZY_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_CRAZY_HPP 1

#include <immintrin.h>

#include <cstdint>

#include <limits>
#include <algorithm>
#include <vector>

enum class crazy_segment_tree_type { sum, min, max };

template<typename T, crazy_segment_tree_type st_type>
constexpr T _id;
template<>
constexpr int32_t _id<int32_t, crazy_segment_tree_type::min> = std::numeric_limits<int32_t>::max();
template<>
constexpr int32_t _id<int32_t, crazy_segment_tree_type::max> = std::numeric_limits<int32_t>::min();

template<typename T, crazy_segment_tree_type st_type>
constexpr T _reduce(T a, T b);
template<>
constexpr int32_t _reduce<int32_t, crazy_segment_tree_type::min>(int32_t a, int32_t b) { return std::min(a, b); }
template<>
constexpr int32_t _reduce<int32_t, crazy_segment_tree_type::max>(int32_t a, int32_t b) { return std::max(a, b); }

template<typename T, crazy_segment_tree_type st_type>
__attribute__((target("sse4.1"))) inline __m128i _reduce(__m128i a, __m128i b);
template<>
__attribute__((target("sse4.1"))) inline __m128i _reduce<int32_t, crazy_segment_tree_type::min>(__m128i a, __m128i b) { return _mm_min_epi32(a, b); }
template<>
__attribute__((target("sse4.1"))) inline __m128i _reduce<int32_t, crazy_segment_tree_type::max>(__m128i a, __m128i b) { return _mm_max_epi32(a, b); }

template<typename T, crazy_segment_tree_type st_type>
__attribute__((target("avx2"))) inline __m256i _reduce(__m256i a, __m256i b);
template<>
__attribute__((target("avx2"))) inline __m256i _reduce<int32_t, crazy_segment_tree_type::min>(__m256i a, __m256i b) { return _mm256_min_epi32(a, b); }
template<>
__attribute__((target("avx2"))) inline __m256i _reduce<int32_t, crazy_segment_tree_type::max>(__m256i a, __m256i b) { return _mm256_max_epi32(a, b); }

constexpr int _ffs(unsigned int x) { return sizeof(unsigned int) * 8 - 1 - __builtin_clz(x); }

// https://codeforces.com/blog/entry/89399
template<crazy_segment_tree_type st_type>
class crazy_segment_tree {
    private: 
    int n, sz;
    using T = int32_t;
    T *st;

    public:
    crazy_segment_tree() {}

    crazy_segment_tree(const std::vector<T> &a) : n(static_cast<int>(a.size())) {
        sz = 1 << ((sizeof(int) << 3) - __builtin_clz(n));
        st = new T[sz << 1];

        for (int i = 0; i < n; i++) st[sz + i] = a[i];
        std::fill(st + sz + n, st + (sz << 1), _id<T, st_type>);

        for (int i = sz - 1; i > 0; i--) st[i] = _reduce<T, st_type>(st[i << 1], st[i << 1 | 1]);
        st[0] = _id<T, st_type>;
    }

    template<typename _Begin, typename _End>
    crazy_segment_tree(const _Begin &b, const _End &e) : crazy_segment_tree(std::vector<T>(b, e)) {} 

    T query() const { return st[1]; }

    T query(int l) const { return st[l + sz]; }

    __attribute__((target("avx2"))) T query(int l, int r) const {
        if (l == r) return st[l + sz];

        int mbit = _ffs(l ^ r), reset = ((1 << mbit) - 1), m = r & ~reset;

        using vecint = T __attribute__((vector_size(32)));
        __m256i identity_vec = _mm256_set1_epi32(_id<T, st_type>);
        vecint vec_ans = (vecint) identity_vec;
        __m256i indexes = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);

        if ((l & reset) != 0) {
            int ll = l - 1 + sz, rr = m - 1 + sz;
            int modbit = 0, maxmodbit = _ffs(ll ^ rr) + 1;

            vecint ll_vec = (vecint) _mm256_srav_epi32(_mm256_set1_epi32(ll), indexes);

    #define LOOP(content) if(modbit + 8 <= maxmodbit) { \
                vec_ans = (vecint)_reduce<T, st_type>((__m256i) vec_ans, _mm256_i32gather_epi32((int*) st, (__m256i) (((ll_vec & 1) - 1) & (ll_vec | 1)), 4)); \
                ll_vec >>= 8; \
                modbit += 8; \
                content \
            }
            LOOP(LOOP(LOOP(LOOP())))
    #undef LOOP

            __m256i tmp = _mm256_i32gather_epi32((int*) st, (__m256i) (((ll_vec & 1) - 1) & (ll_vec | 1)), 4);
            __m256i mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(maxmodbit & 7), indexes);
            vec_ans = (vecint) _reduce<T, st_type>((__m256i) vec_ans, _mm256_blendv_epi8(identity_vec, tmp, mask));
        } else {
            vec_ans[0] = _reduce<T, st_type>(vec_ans[0], st[(l + sz) >> mbit]);
        }

        if((r & reset) != reset) {
            int ll = m + sz, rr = r + 1 + sz;
            int modbit = 0, maxmodbit = _ffs(ll ^ rr) + 1;

            vecint rr_vec = (vecint) _mm256_srav_epi32(_mm256_set1_epi32(rr), indexes);

            #define LOOP(content) if(modbit + 8 <= maxmodbit) { \
                vec_ans = (vecint) _reduce<T, st_type>((__m256i) vec_ans, _mm256_i32gather_epi32((int*) st, (__m256i) (~((rr_vec & 1) - 1) & (rr_vec - 1)), 4)); \
                rr_vec >>= 8; \
                modbit += 8; \
                content \
            }

            LOOP(LOOP(LOOP(LOOP())))

            #undef LOOP

            __m256i tmp = _mm256_i32gather_epi32((int*) st, (__m256i)(~((rr_vec & 1) - 1) & (rr_vec - 1)), 4);
            __m256i mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(maxmodbit & 7), indexes);
            vec_ans = (vecint) _reduce<T, st_type>((__m256i) vec_ans, _mm256_blendv_epi8(identity_vec, tmp, mask));
        } else {
            vec_ans[0] = _reduce<T, st_type>(vec_ans[0], st[(r + sz) >> mbit]);
        }

        __m128i low128 = _mm256_castsi256_si128((__m256i)vec_ans);
        __m128i high128 = _mm256_extractf128_si256((__m256i)vec_ans, 1);
        __m128i ans128 = _reduce<T, st_type>(low128, high128);

        T ans = _id<T, st_type>;
        for (int i = 0; i < 4; i++) ans = _reduce<T, st_type>(ans, ((T __attribute__((vector_size(16))))ans128)[i]); 
        return ans;
    }

    int size() const { return n; }
};

#endif // DATA_STRUCTURES_SEGMENT_TREE_CRAZY_HPP