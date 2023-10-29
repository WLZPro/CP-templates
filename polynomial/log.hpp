#ifndef POLYNOMIAL_LOG_HPP
#define POLYNOMIAL_LOG_HPP 1

#include "polynomial/polynomial.hpp"
#include "polynomial/inv.hpp"

template<typename T>
inline poly<T> log(const poly<T> &a, int n) {
    poly<T> ans = integr(deriv(a) * inv(a, n));
    ans.truncate_to(n);
    return ans;
}

template<typename T>
inline poly<T> log(const poly<T> &a) { return log(a, static_cast<int>(a.size())); }

#endif // POLYNOMIAL_LOG_HPP