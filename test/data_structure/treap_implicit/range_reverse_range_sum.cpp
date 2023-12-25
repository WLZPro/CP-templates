// https://judge.yosupo.jp/problem/range_reverse_range_sum
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/treap_implicit.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    implicit_treap< addition<long long> > tr(a);

    while (q--) {
        int t, l, r; cin >> t >> l >> r; r--;
        switch (t) {
            case 0:
                if (l <= r) tr.reverse(l, r);
                break;
            case 1:
                if (l <= r) cout << tr.query(l, r) << '\n';
                else cout << "0\n";
                break;
            default:
                __builtin_unreachable();
                break;
        }
    }

    return 0;
}