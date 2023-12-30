// https://judge.yosupo.jp/problem/line_add_get_min
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

    vector<int> a(n); vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    vector<long long> pos;
    vector<int> t(q);
    vector< pair<int, long long> > queries(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i];
        if (t[i] == 0) cin >> queries[i].first >> queries[i].second;
        else {
            cin >> queries[i].first;
            pos.push_back(queries[i].first);
        }
    }

    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());

    static_li_chao_tree< linear_function<long long> > lct(pos, {0, numeric_limits<long long>::max()});
    for (int i = 0; i < n; i++) lct.insert({a[i], b[i]});

    for (int i = 0; i < q; i++) {
        if (t[i] == 0) {
            lct.insert({queries[i].first, queries[i].second});
        } else {
            cout << lct.query(queries[i].first) << '\n';
        }
    }

    return 0;
}