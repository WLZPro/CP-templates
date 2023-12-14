#pragma once

#include "math/mod_operations.hpp"
#include "math/primes.hpp"

// Assumptions: `0 <= a < md`
template<typename T>
constexpr T inv_mod_prime(const T &a, const T &md) {
    if (a <= 1) return a;
    return md - mul_mod(md / a, inv_mod_prime(md % a, md), md);
}

// Assumptions: `0 <= a < md`
template<typename T>
constexpr T inv_mod(const T &a, const T &md) {
    T x, y; extgcd_mod(a, md, x, y, md);
    return x;
}

// Assumptions: `0 <= a < md`
template<typename T, T md>
constexpr T inv_mod(const T &a) {
    if constexpr (primes::is_prime_64_bit_v<static_cast<uint64_t>(md)>) return inv_mod_prime(a, md);
    return inv_mod(a, md);
}

template<uint32_t md>
class invs_mod {
    public:
    static constexpr uint32_t mod = md;

    static inline uint32_t computed_up_to = 1;

    // Assumptions: `n < md`
    static void compute_up_to(uint32_t n) {
        if (n <= computed_up_to) return;
        inv.resize(n + 1);
        for (uint32_t a = computed_up_to + 1; a <= n; a++) inv[a] = md - mul_mod(md / a, inv[md % a], md);
        computed_up_to = n;
    }

    // Assumptions: `0 <= a < md`
    static uint32_t get(uint32_t a) {
        if (a <= computed_up_to) return inv[a];
        return inv_mod<uint32_t, md>(a);
    }

    private:
    static inline std::vector<uint32_t> inv = {0, 1};
};