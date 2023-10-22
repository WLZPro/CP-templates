#ifndef MATH_MODINT_HPP
#define MATH_MODINT_HPP 1

#include <algorithm>
#include <iostream>
#include <utility>
#include <tuple>
#include <string>

// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#iterative-version
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
    modint(const T &_x, bool raw = false) { set(_x, raw); }

    template<typename T>
    constexpr modint &operator=(const T &_x) { set(_x); return *this; }

    constexpr modint &operator+=(const modint &rhs) { x += rhs.x; if (x >= MOD) x -= MOD; return *this; }

    constexpr friend modint operator+(modint lhs, const modint &rhs) { return lhs += rhs; }

    constexpr modint &operator-=(const modint &rhs) { x -= rhs.x; if (x < 0) x += MOD; return *this; }

    constexpr friend modint operator-(modint lhs, const modint &rhs) { return lhs -= rhs; }

    constexpr modint &operator*=(const modint &rhs) { x = (unsigned long long) x * rhs.x % MOD; return *this; }

    constexpr friend modint operator*(modint lhs, const modint &rhs) { return lhs *= rhs; }

    constexpr modint inv() const { modint x1, y1; extgcd(x, MOD, x1, y1); return x1; }

    constexpr modint &operator/=(const modint &rhs) { operator*=(rhs.inv()); return *this; }

    constexpr friend modint operator/(modint lhs, const modint &rhs) { return lhs /= rhs; }

    constexpr modint &operator%=(const modint &rhs) { x %= rhs.val(); return *this; }

    constexpr friend modint operator%(modint lhs, const modint &rhs) { return lhs %= rhs; }

#if __cplusplus < 202002L
    constexpr friend bool operator==(const modint &lhs, const modint &rhs) { return lhs.val() == rhs.val(); }
    constexpr friend bool operator!=(const modint &lhs, const modint &rhs) { return !(lhs == rhs); }
    constexpr friend bool operator< (const modint &lhs, const modint &rhs) { return lhs.val() < rhs.val(); }
    constexpr friend bool operator> (const modint &lhs, const modint &rhs) { return rhs < lhs; }
    constexpr friend bool operator<=(const modint &lhs, const modint &rhs) { return !(lhs > rhs); }
    constexpr friend bool operator>=(const modint &lhs, const modint &rhs) { return !(lhs < rhs); }
#else
    constexpr auto operator<=>(const modint&) const = default;
#endif

    constexpr friend std::string to_string(const modint &m) { return to_string(m.x); }

    template<typename T>
    constexpr operator T() const { return x; }

    constexpr int val() const { return x; }
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

using modint1000000007 = modint<1000000007>;
using modint998244353 = modint<998244353>;

#endif // MATH_MODINT_HPP
