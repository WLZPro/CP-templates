// https://judge.yosupo.jp/problem/point_add_range_sum

#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/fenwick_tree.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q; cin >> n >> q;
    
    fenwick_tree< addition<long long> > fenw(n);
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        fenw.update(i, a);
    }

    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 0) fenw.update(x, y);
        else cout << fenw.query(x, y - 1) << '\n';
    }

    return 0;
}
