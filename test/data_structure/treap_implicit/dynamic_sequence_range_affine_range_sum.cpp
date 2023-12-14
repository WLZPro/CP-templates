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
#include "data_structure/treap_implicit.hpp"
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
        a[i].a.set(x, true);
        a[i].sz = 1;
    }

    implicit_treap< addition<info>, hm> tr(a);

    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int i, x; cin >> i >> x;
            tr.insert(i, {x, 1});
        } else if (t == 1) {
            int i; cin >> i;
            tr.erase(i);
        } else if (t == 2) {
            int l, r; cin >> l >> r;
            tr.reverse(l, r - 1);
        } else if (t == 3) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            tr.update(l, r - 1, {mint(b, true), mint(c, true)});
        } else {
            int l, r; cin >> l >> r;
            cout << tr.query(l, r - 1).a.val() << '\n';
        }
    }
    
    return 0;
}