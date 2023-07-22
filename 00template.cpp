#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) 0
#endif

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vll = vector<ll>;
template <class T> using mx_pq = priority_queue<T>;
template <class T> using mn_pq = priority_queue<T, vector<T>, greater<T>>;

const int INF = 0x3f3f3f3f;
const ll LINF = (ll) 1e18;
const double pi = acos(-1);
const double EPS = 1e-9;

void solve(int current_case);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  //cin >> t
  for (int q = 1; q <= t; q++) solve(q);
  return 0;
}

void solve(int current_case) {
  
}
