// https://judge.yosupo.jp/problem/many_aplusb_128bit

#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "math/int128.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        __int128_t a, b; cin >> a >> b;
        cout << a + b << '\n';
    }

    return 0;
}