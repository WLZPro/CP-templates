// https://judge.yosupo.jp/problem/associative_array
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "data_structure/hash_map.hpp"
#include "util/fast_io.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int q; cin >> q;
    safe_unordered_map<unsigned long long, unsigned long long> mp; // or safe_gp_hash_table
    while (q--) {
        int t; unsigned long long k; cin >> t >> k;
        if (t == 0) {
            unsigned long long v; cin >> v;
            mp[k] = v;
        } else {
            cout << mp[k] << '\n';
        }
    }

    return 0;
}