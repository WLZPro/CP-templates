#ifndef MATH_MODINT_HPP
#define MATH_MODINT_HPP 1
 
#include <algorithm>
#include <iostream>
#include <utility>
#include <tuple>
 
/**
 * Compute the greatest common divisor d of a and b together 
 * with some x and y such that ax + by = d using the extended Euclidean algorithm.
 * 
 * @param integers a, b whose gcd will be computed, references x, y where values will be stored.
 * @returns Greatest common divisor of a and b.
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
    void set(const T &_x, bool raw = false) {
        if (raw || (0 <= _x && _x < MOD)) x = _x;
        else {
            x = _x % MOD;
            if (x < 0) x += MOD;
        }
    }
 
    template<typename T>
    modint(const T &_x, bool raw = false) { set(_x, raw); }
 
    template<typename T>
    modint &operator=(const T &_x) { set(_x); return *this; }
 
    modint &operator+=(const modint &rhs) {
        x += rhs.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
 
    template<typename T> 
    modint &operator+=(const T &rhs) { return operator+=(modint(rhs)); }
 
    modint &operator-=(const modint &rhs) {
        x -= rhs.x;
        if (x < 0) x += MOD;
        return *this;
    }
 
    template<typename T> 
    modint &operator-=(const T &rhs) { return operator-=(modint(rhs)); }
 
    modint &operator*=(const modint &rhs) { 
        x = (unsigned long long) x * rhs.x % MOD;
        return *this;
    }
 
    template<typename T> 
    modint &operator*=(const T &rhs) { return operator*=(modint(rhs)); }
 
    modint inv() const {
        modint x1, y1; extgcd(x, MOD, x1, y1);
        return x1;
    }
 
    modint &operator/=(const modint &rhs) {
        operator*=(rhs.inv());
        return *this;
    }
 
    template<typename T> 
    modint &operator/=(const T &rhs) { return operator/=(modint(rhs)); }
 
    modint &operator%=(const modint &rhs) {
        x %= rhs.val();
        return *this;
    }
 
    template<typename T> 
    modint &operator%=(const T &rhs) { return operator%=(modint(rhs)); }
 
    modint &operator++() {
        if (++x == MOD) x = 0;
        return *this;
    }
 
    modint operator++(int) {
        modint tmp(*this); operator++();
        return tmp;        
    }
 
    modint &operator--() {
        if (--x < 0) x = MOD - 1;
        return *this; 
    }
 
    modint operator--(int) {
        modint tmp(*this); operator--();
        return tmp;
    }
 
#if __cplusplus >= 202002L
    inline auto operator<=>(const modint&) const = default;
#endif
 
    template<typename T>
    operator T() const { return x; }
 
    int val() const { return x; }
};
 
template<const int MOD, typename T>
inline modint<MOD> operator+(const modint<MOD> &lhs, const T &rhs) { modint<MOD> tmp = lhs; tmp += rhs; return tmp; }
template<const int MOD, typename T>
inline modint<MOD> operator-(const modint<MOD> &lhs, const T &rhs) { modint<MOD> tmp = lhs; tmp -= rhs; return tmp; }
template<const int MOD, typename T>
inline modint<MOD> operator*(const modint<MOD> &lhs, const T &rhs) { modint<MOD> tmp = lhs; tmp *= rhs; return tmp; }
template<const int MOD, typename T>
inline modint<MOD> operator/(const modint<MOD> &lhs, const T &rhs) { modint<MOD> tmp = lhs; tmp /= rhs; return tmp; }
template<const int MOD, typename T>
inline modint<MOD> operator%(const modint<MOD> &lhs, const T &rhs) { modint<MOD> tmp = lhs; tmp %= rhs; return tmp; }
 
#if __cplusplus < 202002L
 
template<const int MOD>
inline bool operator==(const modint<MOD> &lhs, const modint<MOD> &rhs) { return lhs.val() == rhs.val(); }
template<const int MOD>
inline bool operator!=(const modint<MOD> &lhs, const modint<MOD> &rhs) { return !(lhs == rhs); }
template<const int MOD>
inline bool operator< (const modint<MOD> &lhs, const modint<MOD> &rhs) { return lhs.val() < rhs.val(); }
template<const int MOD>
inline bool operator> (const modint<MOD> &lhs, const modint<MOD> &rhs) { return rhs < lhs; }
template<const int MOD>
inline bool operator<=(const modint<MOD> &lhs, const modint<MOD> &rhs) { return !(lhs > rhs); }
template<const int MOD>
inline bool operator>=(const modint<MOD> &lhs, const modint<MOD> &rhs) { return !(lhs < rhs); }
 
#endif
 
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
