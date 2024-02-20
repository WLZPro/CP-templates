// https://judge.yosupo.jp/submission/192151

#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...)
#endif

#define rep(i, a, b) for (auto i = (a); i < (b); i++)
#define repr(i, a, b) for (auto i = (a) - 1; i >= (b); i--)
#define eb emplace_back
#define pb push_back
#define MP make_pair
#define MT make_tuple
#define all(x) begin(x), end(x)
#define SZ(x) static_cast<int>(x.size())

using ll = long long;
using ull = unsigned ll;
// using lll = __int128_t;
// using ulll = __uint128_t;

using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;

template<typename T> constexpr bool cmax(T &a, const T &b) { return a < b ? a = b, true : false; }
template<typename T> constexpr bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }

constexpr int inf = 0x3f3f3f3f;
constexpr ll linf = (ll) 1e18;
constexpr double dinf = numeric_limits<double>::infinity();
constexpr double eps = 1e-9;

void solve();

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    for (int q = 1; q <= t; q++) solve();
    return 0;
}

// https://github.com/kth-competitive-programming/kactl/blob/main/content/various/BumpAllocator.h
static char buf[450 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}

struct node {
    node *l, *r;
    ll c; int u, s;
};

inline int s_val(node *t) {
    return !t ? 0 : t->s;
}

node *merge(node *l, node *r) {
    // debug((ll) l);
    if (!l) return r;
    if (!r) return l;
    if (l->c > r->c) return merge(r, l);
    node *t = new node{l->l, merge(l->r, r), l->c, l->u, 0};
    if (s_val(t->l) < s_val(t->r)) swap(t->l, t->r);
    t->s = s_val(t->r) + 1;
    return t;
}

node *insert(node *t, ll c, int u) {
    return merge(t, new node{0, 0, c, u, 1});
}

void solve() {
    int n, m, s, t, k; cin >> n >> m >> s >> t >> k;
    vector g(n, vector< pair<int, ll> >()), tg = g;
    rep(i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        g[u].eb(v, w); tg[v].eb(u, w);
    }
    vll dist(n, linf); dist[t] = 0;
    vi p(n, -1);
    priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater<> > pq; pq.emplace(0, t);
    vector<vi> g2(n, vi());
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (p[u] != -1) {
            g2[p[u]].pb(u);
        }
        for (auto &[v, w] : tg[u]) {
            if (cmin(dist[v], d + w)) {
                p[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    vector<node*> heap(n, 0);
    queue<int> q; q.push(t);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u != t) heap[u] = heap[p[u]];
        bool b = 0;
        for (auto &[v, w] : g[u]) {
            if (dist[v] == linf) continue;
            ll c = w + dist[v] - dist[u];
            if (!b && v == p[u] && c == 0) { b = 1; continue; }
            heap[u] = insert(heap[u], c, v);
        }
        for (auto &v : g2[u]) q.push(v);
    }
    priority_queue< pair<ll, node*>, vector< pair<ll, node*> >, greater<> > pq2;
    if (heap[s]) pq2.emplace(heap[s]->c, heap[s]);

    if (dist[s] < linf) cout << dist[s] << '\n';
    else cout << -1 << '\n';

    cerr << dist[s] << endl;
    rep(i, 0, k - 1) {
        if (dist[s] == linf || pq2.empty()) { cout << -1 << '\n'; continue; }
        auto [d, h] = pq2.top(); pq2.pop();
        cout << dist[s] + d << '\n';
        if (heap[h->u]) pq2.emplace(d + heap[h->u]->c, heap[h->u]);
        if (h->l) pq2.emplace(d - h->c + h->l->c, h->l);
        if (h->r) pq2.emplace(d - h->c + h->r->c, h->r);
    }
}