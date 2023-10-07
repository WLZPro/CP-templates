#ifndef MATH_MODINT_HPP
#define MATH_MODINT_HPP 1

#include <algorithm>
#include <iostream>
#include <utility>
#include <tuple>

/**
 * Compute the greatest common divisor d of a and b together 
 * with the x and y such that ax + by = d using the extended Euclidean algorithm
 * 
 * @param integers a, b whose gcd will be computed, references x, y where values will be stored
 * @returns greatest common divisor of a and b
*/
template<typename T1, typename T2>
T1 extgcd(const T1& a, const T1& b, T2 &x, T2 &y) {
    x = 1; y = 0;
    T1 a1(a), b1(b);
    T2 x1 = 0, y1 = 1;
    while (b1 != 0) {
        T1 q = a1 / b1;
        std::tie(x, x1) = std::make_pair(x1, x - q * x1);
        std::tie(y, y1) = std::make_pair(y1, y - q * y1);
        std::tie(a1, b1) = std::make_pair(b1, a1 - q * b1);
    }
    return a1;
}

/**
 * Modular integer implementation
 * NOT completely tested!
*/
template<const int MOD>
class modint {
    private: int x;

    public:
    modint() : x(0) {}

    template<typename T>
    void set(const T _x, bool raw = false) {
        if (raw || (0 <= _x && _x < MOD)) x = _x;
        else {
            x = _x % MOD;
            if (x < 0) x += MOD;
        }
    }

    template<typename T>
    modint(const T &_x, bool raw = false) {
        set(_x, raw);
    }

    template<typename T>
    modint<MOD> &operator=(const T &_x) {
        set(_x);
        return *this;
    }

    modint<MOD> &operator+=(const modint<MOD> &rhs) {
        x += rhs.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }

    friend modint<MOD> operator+(modint<MOD> lhs, const modint<MOD> &rhs) {
        lhs += rhs;
        return lhs;
    }

    modint<MOD> &operator-=(const modint<MOD> &rhs) {
        x -= rhs.x;
        if (x < 0) x += MOD;
        return *this;
    }

    friend modint<MOD> operator-(modint<MOD> lhs, const modint<MOD> &rhs) {
        lhs -= rhs;
        return lhs;
    }

    modint<MOD> &operator*=(const modint<MOD> &rhs) {
        x = (unsigned long long) x * rhs.x % MOD;
        return *this;
    }

    friend modint<MOD> operator*(modint<MOD> lhs, const modint<MOD> &rhs) {
        lhs *= rhs;
        return lhs;
    }

    modint<MOD> inv() const {
        modint x1, y1;
        extgcd(x, MOD, x1, y1);
        return std::move(x1);
    }

    modint<MOD> &operator/=(const modint<MOD> &rhs) {
        operator*=(rhs.inv());
        return *this;
    }

    friend modint<MOD> operator/(modint<MOD> lhs, const modint<MOD> &rhs) {
        lhs /= rhs;
        return lhs;
    }

    modint<MOD> &operator%=(const modint<MOD> &rhs) {
        x %= rhs.val();
        return *this;
    }

    friend modint<MOD> operator%(modint<MOD> lhs, const modint<MOD> &rhs) {
        lhs %= rhs;
        return lhs;
    }

    friend bool operator==(const modint<MOD> &lhs, const modint<MOD> &rhs) {
        return lhs.val() == rhs.val();
    }

    friend bool operator!=(const modint<MOD> &lhs, const modint<MOD> &rhs) {
        return !(lhs == rhs);
    }

    friend bool operator< (const modint<MOD> &lhs, const modint<MOD> &rhs) { return lhs.val() < rhs.val(); }
    friend bool operator> (const modint<MOD> &lhs, const modint<MOD> &rhs) { return rhs < lhs; }
    friend bool operator<=(const modint<MOD> &lhs, const modint<MOD> &rhs) { return !(lhs > rhs); }
    friend bool operator>=(const modint<MOD> &lhs, const modint<MOD> &rhs) { return !(lhs < rhs); }

    template<typename T>
    operator T() const {
        return x;
    }

    int val() const {
        return x;
    }
};

template<const int MOD, typename T>
modint<MOD> pow(const modint<MOD> &_a, const T &_b) {
    modint<MOD> ans(1, true), a(_a, true);
    T b(_b);
    while (b > 0) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

template<const int MOD>
std::istream &operator>>(std::istream &is, modint<MOD> &x) {
    unsigned int _x;
    is >> _x;
    x.set(_x, true);
    return is;
}

template<const int MOD>
std::ostream &operator<<(std::ostream &os, const modint<MOD> &x) {
    os << x.val();
    return os;
}

using mint1000000007 = modint<1000000007>;
using mint998244353 = modint<998244353>;

#endif // MATH_MODINT_HPP