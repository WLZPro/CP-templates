// https://codeforces.com/contest/1354/problem/D
#include <bits/stdc++.h>
using namespace std;

#include "data_structure/fenwick_tree.hpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  fenwick_tree< addition<int> > fenw(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    fenw.update(x - 1, +1);
  }
  while (q--) {
    int k;
    cin >> k;
    if (k >= 1) {
      fenw.update(k - 1, +1);
    } else {
      int lo = fenw.search([&](int x) { return x >= -k; });
      fenw.update(lo, -1);
    }
  }
  int prev = fenw.query(0);
  if (prev > 0) {
    cout << 1 << '\n';
    return 0;
  }
  for (int i = 0; i < n; i++) {
    int tmp = fenw.query(i);
    if (tmp > prev) {
      cout << i + 1 << '\n';
      return 0;
    }
    prev = tmp;
  }
  cout << 0 << '\n';
  return 0;
}
