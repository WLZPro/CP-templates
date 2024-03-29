// https://judge.yosupo.jp/problem/staticrmq

#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/sparse_table.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sparse_table< minimum<int> > st(a);
    debug(st);

    while (q--) {
        int l, r; cin >> l >> r;
        cout << st.query(l, r - 1) << '\n';
    }
    
    return 0;
}
