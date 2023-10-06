#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) 0
#endif

#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define eb emplace_back
#define pb push_back
#define MP make_pair
#define MT make_tuple
#define all(x) (x).begin(), (x).end()
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
template<typename T> using max_pq = priority_queue<T>;
template<typename T> using min_pq = priority_queue<T, vector<T>, greater<T>>;

template<typename T> void cmax(T &a, const T &b) { a = max(a, b); }
template<typename T> void cmin(T &a, const T &b) { a = min(a, b); }

const int INF = 0x3f3f3f3f;
const ll LINF = (ll) 1e18;
const double DINF = 1.0 / 0.0;
const double pi = acos(-1);
const double EPS = 1e-9;

void solve(int current_case);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    for (int q = 1; q <= t; q++) solve(q);
    return 0;
}



void solve(int current_case) {
    
}
