#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) 0
#endif

#define rep(i,a,b) for(auto i=(a)-((a)>(b));i!=(b)-((a)>(b));i+=1-2*((a)>(b)))
#define eb emplace_back
#define pb push_back
#define MP make_pair
#define MT make_tuple
#define all(x) begin(x), end(x)
#define SZ(x) (int) x.size()

using ll = long long;
using ull = unsigned ll;
using lll = __int128_t;
using ulll = __uint128_t;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;

template<typename T> void cmax(T &a, const T &b) { a = max(a, b); }
template<typename T> void cmin(T &a, const T &b) { a = min(a, b); }

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (ll) 1e18;
constexpr double DINF = numeric_limits<double>::infinity();
constexpr double EPS = 1e-9;

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    for (int q = 1; q <= t; q++) solve();
    return 0;
}



void solve() {
    
}
