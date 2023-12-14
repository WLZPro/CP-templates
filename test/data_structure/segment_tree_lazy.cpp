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

struct info { mint a; int sz; };

template<>
struct addition<info> {
    using T = info;

    static constexpr info e = {0, 0};
    static constexpr info op(const info &lhs, const info &rhs) {
        return {lhs.a + rhs.a, lhs.sz + rhs.sz};
    }
};

struct hm {
    struct func { mint a, b; };
    using T = func;

    static constexpr func id = {1, 0};
    static constexpr info map(const func &f, const info &x) {
        return {f.a * x.a + f.b * x.sz, x.sz};
    }
    static constexpr func comp(const func &f, const func &g) {
        return {f.a * g.a, f.a * g.b + f.b};
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;

    vector<info> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i].a = x; a[i].sz = 1;
    }

    lazy_segtree< addition<info>, hm> st(a);
    while (q--) {
        int t, l, r; cin >> t >> l >> r; r--;
        if (t == 0) {
            int c, d; cin >> c >> d;
            st.update(l, r, {c, d});
        } else {
            cout << st.query(l, r).a.val() << '\n';
        }
    }
    return 0;
}