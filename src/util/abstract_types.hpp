#pragma once

#include <limits>

struct _null_t { using T = _null_t; };

// Semigroup, Monoid, Group, AbelianGroup
// DO NOT use as update with addition
template<typename _T>
struct addition {
    using T = _T;

    static constexpr T e = 0;
    static constexpr T op(const T &a, const T &b) { return a + b; };    
    static constexpr T inv(const T &a) { return -a; }
    static constexpr T map(const T &a, const T &b) { return a + b; }
    static constexpr T comp(const T &a, const T &b) { return a + b; }
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

template<typename T> constexpr bool has_map_with_implicit_size_v = false;

template<typename S>
struct id_map {
    using T = bool;

    static constexpr const S &map(const bool&, const S &s) { return s; } 
    static constexpr const bool &comp(const bool &a, const bool&) { return a; }
};

template<typename _T>
struct addition_with_sum {
    using T = _T;

    static constexpr T map(const T &x, const T &a) { return a + x; }
    static constexpr T map(const T &x, const T &a, int sz) { return a + x * sz; }
    static constexpr T comp(const T &x, const T &y) { return x + y; }
};
template<typename T> constexpr bool has_map_with_implicit_size_v< addition_with_sum<T> > = true;

// DO NOT use with addition
template<typename _T>
struct assignment {
    using T = _T;

    static constexpr T map(const T &x, const T&) { return x; }
    static constexpr T comp(const T &x, const T&) { return x; }
};

template<typename _T>
struct assignment_with_sum {
    using T = _T;

    static constexpr T map(const T &x, const T&) { return x; }
    static constexpr T map(const T &x, const T&, int sz) { return x * sz; }
    static constexpr T comp(const T &x, const T&) { return x; }
};
template<typename T> constexpr bool has_map_with_implicit_size_v< assignment_with_sum<T> > = true;

template<typename S>
struct range_affine {
    struct func { S a, b; }; 
    using T = func;

    static constexpr S map(const func &f, const S &x) { return f.a * x + f.b; }
    static constexpr S map(const func &f, const S &x, int sz) { return f.a * x + f.b * sz; }
    static constexpr func comp(const func &f, const func &g) { return {f.a * g.a, f.a * g.b + f.b}; }
};
template<typename T> constexpr bool has_map_with_implicit_size_v< range_affine<T> > = true;