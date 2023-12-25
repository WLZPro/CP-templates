// https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
#include <iostream>
#include <vector>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/treap_implicit.hpp"
#include "math/modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;

    vector<mint> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    implicit_treap< addition<mint>, range_affine<mint> > tr(a);

    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int i; mint x; cin >> i >> x;
            tr.insert(i, x);
        } else if (t == 1) {
            int i; cin >> i;
            tr.erase(i);
        } else if (t == 2) {
            int l, r; cin >> l >> r;
            tr.reverse(l, r - 1);
        } else if (t == 3) {
            int l, r; mint b, c;
            cin >> l >> r >> b >> c;
            tr.update(l, r - 1, {b, c});
        } else {
            int l, r; cin >> l >> r;
            cout << tr.query(l, r - 1) << '\n';
        }
    }
    
    return 0;
}