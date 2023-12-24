// https://judge.yosupo.jp/problem/zalgorithm
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "string/z_function.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string s; cin >> s;
    vector<int> z = z_function(s); z[0] = static_cast<int>(s.length());

    for (const int &x : z) cout << x << ' ';
    cout << '\n';

    return 0;
}