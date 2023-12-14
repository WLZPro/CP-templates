#include <iostream>
#include <algorithm>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/treap_implicit.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        implicit_treap< addition<char> > tr(vector<char>(s.begin(), s.end()));
    
        vector<int> l(k), r(k);
        for (int i = 0; i < k; i++) cin >> l[i];
        for (int i = 0; i < k; i++) cin >> r[i];
    
        int q; cin >> q;
        while (q--) {
            int x; cin >> x;
            int i = upper_bound(l.begin(), l.end(), x) - l.begin() - 1;
            int a = min(x, r[i] + l[i] - x), b = max(x, r[i] + l[i] - x);
            a--; b--;
            tr.reverse(a, b);
        }
    
        for (int i = 0; i < n; i++) cout << tr[i];
        cout << '\n';
    }

    return 0;
}