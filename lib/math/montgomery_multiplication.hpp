#pragma once

#include <cstdint>
#include <limits>

// https://github.com/maspypy/library/blob/main/mod/mongomery_modint.hpp
template<typename uintx_t, typename uint2x_t>
class montgomery_multiplication {
    public:
    constexpr montgomery_multiplication() {}
    constexpr montgomery_multiplication(uintx_t _md) { set_mod(_md); }

    constexpr void set_mod(uintx_t _md) {
        md = _md; n2 = -static_cast<uint2x_t>(md) % md; r = md;
        for (int i = 0; i < 5; i++) r *= 2 - md * r;
        r = -r;
    }

    // Assumptions: `0 <= x, y < 2 * mod`
    constexpr uintx_t mul(uintx_t x, uintx_t y) const { return reduce(static_cast<uint2x_t>(x) * y); }

    // Assumptions: `0 <= a < 2 * mod`
    template<typename T>
    constexpr uintx_t pow(uintx_t a, T b) const {
        uintx_t ans = convert(1);
        for (; b; b >>= 1, a = mul(a, a)) if (b & 1) ans = mul(ans, a);
        return ans;
    }

    constexpr bool equiv(uintx_t x, uintx_t y) { return (x >= md ? x - md : x) == (y >= md ? y - md : y); }    

    constexpr uintx_t mod() const { return md; }

    constexpr uintx_t convert(uintx_t x) const { return reduce(static_cast<uint2x_t>(x) * n2); }

    constexpr uintx_t reduce(uint2x_t x) const { return (x + static_cast<uint2x_t>(static_cast<uintx_t>(x) * r) * md) >> w; }

    private:
    static constexpr int w = std::numeric_limits<uintx_t>::digits;

    uintx_t md, r, n2;
};

using montgomery_multiplication_32 = montgomery_multiplication<uint32_t, uint64_t>;
using montgomery_multiplication_64 = montgomery_multiplication<uint64_t, __uint128_t>;

template<typename uintx_t, typename uint2x_t, int id> montgomery_multiplication<uintx_t, uint2x_t> global_montgomery_multiplication;
template<int id> montgomery_multiplication_32 &global_montgomery_multiplication_32 = global_montgomery_multiplication<uint32_t, uint64_t, id>;
template<int id> montgomery_multiplication_64 &global_montgomery_multiplication_64 = global_montgomery_multiplication<uint64_t, __uint128_t, id>;