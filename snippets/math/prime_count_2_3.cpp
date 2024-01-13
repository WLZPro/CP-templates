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

// Semigroup, Monoid, Group, AbelianGroup
template<typename _T>
struct addition {
    using T = _T;

    static constexpr T e = 0;
    static constexpr T op(const T &a, const T &b) { return a + b; };    
    static constexpr T inv(const T &a) { return -a; }
    static constexpr T map(const T &a, const T &b) { return a + b; }
    static constexpr T comp(const T &a, const T &b) { return a + b; }
};

// https://github.com/the-tourist/algo/blob/master/data/fenwick.cpp
template<typename G>
class fenwick_tree {
    public:
    using T = typename G::T;

    fenwick_tree() : n(0) {}
    explicit fenwick_tree(int _n) : n(_n), fenw(n, G::e) {
        #ifdef DEBUG
        _dbg.assign(n, G::e);
        #endif
    }
    
    // https://codeforces.com/blog/entry/63064
    explicit fenwick_tree(const std::vector<T> &a) : fenwick_tree(a.size()) {
        #ifdef DEBUG
        _dbg = a;
        #endif

        for (int i = 0; i < n; i++) {
            fenw[i] = G::op(fenw[i], a[i]);
            if ((i | (i + 1)) < n) fenw[i | (i + 1)] = G::op(fenw[i | (i + 1)], fenw[i]);
        }
    }

    void update(int idx, const T &val) {
        #ifdef DEBUG
        _dbg[idx] = G::op(_dbg[idx], val);
        #endif

        for (; idx < n; idx |= (idx + 1)) fenw[idx] = G::op(fenw[idx], val);
    }

    T query(int idx) const {
        T ans = G::e;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ans = G::op(ans, fenw[idx]);
        return ans;
    }

    T query(int l, int r) const {
        if (l > r) return G::e;
        if (l == 0) return query(r);
        return G::op(query(r), G::inv(query(l - 1)));
    };

    T operator[](int idx) const { return query(idx, idx); }

    friend std::string to_string(const fenwick_tree &ft) {
        #ifdef DEBUG
        return to_string(ft._dbg);
        #else
        return "";
        #endif
    }

    private:
    int n;
    std::vector<T> fenw;

    #ifdef DEBUG
    std::vector<T> _dbg;
    #endif
};

// https://codeforces.com/blog/entry/91632
ll prime_count(ll N) {
    int y = powl(N, 1.1/3.), z = N / y, py = 0; // pi(y)
    vi pr = {1}, spf(z + 1, 0);
    rep(m, 2, z + 1) {
        if (!spf[m]) {
            if (m <= y) py = SZ(pr);
            spf[m] = SZ(pr);
            pr.pb(m);
        }
        rep(i, 1, SZ(pr)) {
            if (i > spf[m] || m * pr[i] > z) break;
            spf[m * pr[i]] = i;
        }
    }
    spf[1] = SZ(pr);
    ll F = 0;
    for (int i = SZ(pr) - 1, j = py + 1; i > py; i--) {
        while (j < SZ(pr) && (ll) pr[i] * pr[j] <= N) j++;
        F += min(i + 1, j) - py - 1;
    }
    ll phi = 0; // phi(n, pi(y))
    vector< tuple<int, int, int> > queries;
    auto calc_phi = [&](auto &&self, ll n, int a, int sgn = 1) -> void {
        if (a == 0) {
            phi += sgn * n;
            return;
        }
        if (n <= z) {
            queries.eb(n, a, sgn);
            return;
        }
        // phi(n, a) = phi(n, a - 1) - phi(n / p_a, a - 1)
        self(self, n, a - 1, sgn);
        self(self, n / pr[a], a - 1, -sgn);
    };
    calc_phi(calc_phi, N, py);
    sort(all(queries));
    fenwick_tree< addition<ll> > ft(SZ(pr));
    for (int cm = 1; auto &[m, a, sgn] : queries) {
        while (cm <= m) ft.update(SZ(pr) - spf[cm++], +1);
        phi += sgn * ft.query(SZ(pr) - a - 1);
    }
    return phi + py - F - 1;
}

void solve() {
    ll N; cin >> N;
    cout << prime_count(N) << '\n';
}
