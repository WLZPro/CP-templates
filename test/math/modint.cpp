// modint.hpp compilation test
// g++ -std=c++17 (-DDEBUG) modint.cpp
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "math/modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    constexpr mint a = 5;
    constexpr mint b = a + a, c = b - a, d = a * a;
    constexpr mint e = a.inv_constexpr(), f = a * e;
    constexpr int g = a.val();
    constexpr long long h = (long long) a;
    constexpr bool b1 = f == 1;
    constexpr mint i(100000000ull * mint::mod + 12480593ull), j((char) 20);

    mint x = 1; x++; x--; ++x; --x;
    mint y = 1; x += y; x -= y; x *= y; x /= y;
    x == y; x != y; x > y; x < y; x >= y; x <= y;

    cin >> y; cout << y;

    debug(y);

    mint::compute_inverses(10);
    mint::compute_factorials(10);

    cout << mint::inv(4) << '\n';
    cout << mint::fact(4) << '\n';
    cout << mint::inv_fact(4) << '\n';
    cout << mint::binom(4, 2) << '\n';
    cout << mint::catalan(4) << '\n';

    return 0;
}