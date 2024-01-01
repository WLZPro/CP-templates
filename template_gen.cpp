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

mt19937_64 rng;

void seed(ll x) {
    rng.seed(x);
}

template<typename T = ll>
T rand(T a, T b) {
    return uniform_int_distribution<T>(a, b)(rng);
}

template<typename T = ll>
T rand(T a) { return rand(static_cast<T>(1), a); }

template<typename T = double>
T randr(T a, T b) {
    return uniform_real_distribution<T>(a, b)(rng);
}

template<typename T = double>
T randr(T a = 1) { return randr(static_cast<T>(0), a); }

int main(int argc, char **argv) {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    if (argc > 1) seed(atoi(argv[1]));
    else seed(chrono::steady_clock().now().time_since_epoch().count());

    return 0;
}