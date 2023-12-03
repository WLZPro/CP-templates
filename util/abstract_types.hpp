#pragma once

#include <limits>

// Semigroup, Monoid, Group, AbelianGroup
template<typename _T>
struct addition {
    using T = _T;

    static constexpr T e = 0;
    static constexpr T op(const T &a, const T &b) { return a + b; };    
    static constexpr T inv(const T &a) { return -a; }
};

// Semigroup, Monoid
template<typename _T>
struct minimum {
    using T = _T;

    static constexpr T e = std::numeric_limits<T>::max();
    static constexpr const T &op(const T &a, const T &b) { return a < b ? a : b; }
};

// Semigroup, Monoid
template<typename _T>
struct maximum {
    using T = _T;

    static constexpr T e = std::numeric_limits<T>::min();
    static constexpr const T &op(const T &a, const T &b) { return a < b ? b : a; }
};