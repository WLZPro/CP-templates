// https://judge.yosupo.jp/problem/static_range_sum

#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/segment_tree.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    segment_tree< addition<long long> > st(a);
    debug(st);

    while (q--) {
        int l, r; cin >> l >> r;
        cout << st.query(l, r - 1) << '\n';
    }

    return 0;
}
