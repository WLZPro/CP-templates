// https://judge.yosupo.jp/problem/range_affine_range_sum

#include <iostream>
#include <vector>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/segment_tree_lazy.hpp"
#include "math/modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;

    vector<mint> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    lazy_segtree< addition<mint>, range_affine<mint> > st(a);
    while (q--) {
        int t, l, r; cin >> t >> l >> r; r--;
        if (t == 0) {
            int c, d; cin >> c >> d;
            st.update(l, r, {c, d});
        } else {
            cout << st.query(l, r) << '\n';
        }
    }
    return 0;
}