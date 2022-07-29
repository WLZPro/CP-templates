#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int w_mx = 15311432;
const int w_mx_inv = 469870224;

int add(int a, int b) {
  if (a + b >= MOD) return a + b - MOD;
  return a + b;
}

int sub(int a, int b) {
  return add(a, MOD - b);
}

int mul(int a, int b) {
  return (long long) a * b % MOD;
}

int modpow(int b, int p) {
  if (p == 0) return 1;
  int ans = modpow(mul(b, b), p / 2);
  if (p % 2 == 1) ans = mul(ans, b);
  return ans;
}

int extgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int x1, y1, g = extgcd(b, a % b, x1, y1);
  x = y1; y = sub(x1, mul(y1, (a / b) % MOD));
  return g;
}
 
int inv(int x) {
  int x1, y1;
  extgcd(x, MOD, x1, y1);
  return x1;
}

vector<int> ntt(const vector<int> &_a, bool invert = false) {
  vector<int> a = _a;
  int n = (int) a.size();
  assert((n & (n - 1)) == 0);
  for (int i = 1, j = 0; i < n; i++) {
    int k = n >> 1;
    for (; j & k; k >>= 1) j ^= k;
    j ^= k;
    if (i < j) swap(a[i], a[j]);
  }
  for (int k = 1; (1 << k) <= n; k++) {
    int w_2_k = invert ? w_mx_inv : w_mx;
    w_2_k = modpow(w_2_k, modpow(2, 23 - k));
    for (int i = 0; i < n; i += (1 << k)) {
      int w = 1;
      for (int j = 0; j < (1 << (k - 1)); j++) {
        int u = a[i + j], v = mul(w, a[i + j + (1 << (k - 1))]);
        a[i + j] = add(u, v);
        a[i + j + (1 << (k - 1))] = sub(u, v);
        w = mul(w, w_2_k);
      }
    }
  }
  if (invert) {
    int n_inv = inv(n);
    for (auto &x : a) x = mul(x, n_inv);
  }
  return move(a);
}

vector<int> poly_mul(const vector<int> &_a, const vector<int> &_b) {
  vector<int> a = _a, b = _b;
  while ((int) a.size() < (int) b.size()) a.push_back(0);
  while ((int) b.size() < (int) a.size()) b.push_back(0);
  while (((int) a.size()) & ((int) a.size() - 1)) a.push_back(0);
  while (((int) b.size()) & ((int) b.size() - 1)) b.push_back(0);
  int n = (int) a.size();
  for (int i = 0; i < n; i++) a.push_back(0), b.push_back(0);
  a = ntt(a); b = ntt(b);
  vector<int> c(2 * n);
  for (int i = 0; i < 2 * n; i++) c[i] = mul(a[i], b[i]);
  return move(ntt(c, true));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m; // poly_mul example
  cin >> n >> m;
  vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];
  vector<int> c = poly_mul(a, b);
  while (!c.empty() && c.back() == 0) c.pop_back();
  for (auto &x : c) cout << x << ' ';
  cout << endl;
  return 0;
}
