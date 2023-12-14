// https://oj.uz/problem/view/COCI21_index

#include <iostream>
#include <vector>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/segment_tree_persistent.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int> p(n + 1);
    vector< vector<int> > mp((int) 2e5 + 5);
    for (int i = 1; i <= n; i++) cin >> p[i], mp[p[i]].push_back(i);

    psegtree< addition<int> > st(n + 1, 0);
    vector<int> roots((int) 2e5 + 5); roots[(int) 2e5 + 1] = st.original_root();

    for (int i = (int) 2e5; i >= 0; i--) {
        roots[i] = roots[i + 1];
        for (auto &idx : mp[i]) roots[i] = st.update(roots[i], idx, 1);
    }

    while (q--) {
        int l, r; cin >> l >> r;
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (st.query(roots[mid], l, r) >= mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        cout << lo << '\n';
    }

    return 0;
}