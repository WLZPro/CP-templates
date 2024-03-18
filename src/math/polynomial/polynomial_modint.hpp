#pragma once

#include "math/polynomial/polynomial.hpp"
#include "math/modint.hpp"
#include "math/polynomial/ntt_montgomery.hpp"

#include <cstring>

template<uint32_t md>
class polynomial< modint<md> > : public poly_base< modint<md> > {
    public:
    using poly_base< modint<md> >::poly_base;

    inline polynomial &operator*=(const polynomial &rhs) {
        if (this->empty() || rhs.empty()) return *this = {};
        int n = this->size() + rhs.size() - 1;
        int k = __lg(n - 1) + 1;

        this->resize(1 << k);
        uint32_t *cache = new uint32_t[1 << k]();
        memcpy(cache, rhs.data(), sizeof(uint32_t) * rhs.size());

        ntt::conv_via_montgomery<md>(reinterpret_cast<uint32_t*>(this->data()), cache, k);
        this->resize(n);
        return *this;
    }

    inline friend polynomial operator*(polynomial lhs, const polynomial &rhs) {
        return lhs *= rhs;
    }
};

// Defined in power_series_inv.hpp
template<uint32_t md>
inline void inv_via_montgomery(uint32_t*, uint32_t*, uint32_t*, int);

template<bool leak = true, uint32_t md>
inline polynomial< modint<md> > inv(const polynomial< modint<md> > &P, int n) {
    int k = __lg(n - 1) + 1;
    polynomial< modint<md> > Q(1 << (k + 1));
    uint32_t *a = new uint32_t[1 << (k + 1)](),
             *b = reinterpret_cast<uint32_t*>(Q.data()),
             *c = new uint32_t[1 << (k + 1)]();
    memcpy(a, P.data(), sizeof(uint32_t) * P.size());
    inv_via_montgomery<md>(a, b, c, k);
    Q.resize(n);

    if constexpr (!leak) delete[] a, delete[] c;
    return Q;
}

template<bool leak = true, uint32_t md>
inline polynomial< modint<md> > inv(const polynomial< modint<md> > &P) {
    return inv<leak, md>(P, P.size());
}

// Defined in power_series_log.hpp
template<uint32_t md>
void log_via_montgomery(uint32_t*, uint32_t*, uint32_t*, int);

template<bool leak = true, uint32_t md>
inline polynomial< modint<md> > log(const polynomial< modint<md> > &P, int n) {
    int k = __lg(n - 1) + 1;
    polynomial< modint<md> > Q(1 << (k + 1));
    uint32_t *a = new uint32_t[1 << (k + 1)](),
             *b = reinterpret_cast<uint32_t*>(Q.data()),
             *c = new uint32_t[1 << (k + 1)]();
    memcpy(a, P.data(), sizeof(uint32_t) * P.size());
    log_via_montgomery<md>(a, b, c, k);
    Q.resize(n);

    if constexpr (!leak) delete[] a, delete[] c;
    return Q;
}

template<bool leak = true, uint32_t md>
inline polynomial< modint<md> > log(const polynomial< modint<md> > &P) {
    return log<leak, md>(P, P.size());
}