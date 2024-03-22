// https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "external/fast_io_nor.hpp"
#include "data_structure/splay_tree_implicit.hpp"
#include "math/modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<mint> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    implicit_splay_tree< addition<mint>, range_affine<mint> > st(a);

    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int i; mint x; cin >> i >> x;
            st.insert(i, x);
        } else if (t == 1) {
            int i; cin >> i;
            st.erase(i, i);
        } else if (t == 2) {
            int l, r; cin >> l >> r; --r;
            st.reverse(l, r);
        } else if (t == 3) {
            int l, r; mint b, c; cin >> l >> r >> b >> c; --r;
            st.update(l, r, {b, c});
        } else {
            int l, r; cin >> l >> r; --r;
            cout << st.query(l, r) << '\n';
        }
    }
}
