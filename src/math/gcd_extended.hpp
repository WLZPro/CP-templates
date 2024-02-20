#pragma once

#include <utility>

#include "math/mod_operations.hpp"

// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#iterative-version
template<typename T>
constexpr T extgcd(T a, T b, T &x, T &y) {
    x = 1; y = 0;
    T x1(0), y1(1);
    while (b) {
        T q = a / b;
        x = std::exchange(x1, x - q * x1);
        y = std::exchange(y1, y - q * y1);
        a = std::exchange(b, a - q * b);
    }
    return a;
}