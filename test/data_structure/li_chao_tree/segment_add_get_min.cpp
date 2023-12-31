// https://judge.yosupo.jp/problem/segment_add_get_min
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#include "util/fast_io.hpp"
#include "data_structure/li_chao_tree.hpp"

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    int n, q; cin >> n >> q;

    vector<int> l(n), r(n), a(n); vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i] >> a[i] >> b[i];

    vector<long long> pos;
    vector<int> t(q);
    vector< tuple<int, int, int, long long> > queries(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i];
        if (t[i] == 0) cin >> get<0>(queries[i]) >> get<1>(queries[i]) >> get<2>(queries[i]) >> get<3>(queries[i]);
        else cin >> get<0>(queries[i]), pos.push_back(get<0>(queries[i]));
    }

    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());

    static_li_chao_tree< linear_function<long long> > lct(pos, {0, numeric_limits<long long>::max()});
    for (int i = 0; i < n; i++) lct.insert(l[i], r[i] - 1, {a[i], b[i]});

    for (int i = 0; i < q; i++)
        if (t[i] == 0)
            lct.insert(get<0>(queries[i]), get<1>(queries[i]) - 1, {get<2>(queries[i]), get<3>(queries[i])});
        else {
            long long ans = lct.query(get<0>(queries[i]));
            if (ans > (long long) 9e18) cout << "INFINITY\n";
            else cout << ans << '\n';
        }

    return 0;
}