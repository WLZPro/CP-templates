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



void solve() {
    
}
