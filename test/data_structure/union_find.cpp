#include <iostream>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/union_find.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q; cin >> n >> q;
    union_find uf(n);    
    while (q--) {
        int t, u, v; cin >> t >> u >> v;
        if (t == 0) uf.connect(u, v);
        else cout << uf.connected(u, v) << '\n';
        debug(uf);
    }

    return 0;
}