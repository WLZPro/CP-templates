// https://judge.yosupo.jp/problem/staticrmq

#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/segment_tree_avx.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    avx_segment_tree< minimum<int> > st(a);

    while (q--) {
        int l, r; cin >> l >> r;
        cout << st.query(l, r - 1) << '\n';
    }

    return 0;
}