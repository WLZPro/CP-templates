// https://judge.yosupo.jp/problem/range_kth_smallest
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/wavelet_tree.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    wavelet_tree wt(a);

    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << wt.find_by_order(l, r, k) << '\n';
    }

    return 0;    
}