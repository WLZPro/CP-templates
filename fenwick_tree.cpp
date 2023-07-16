#include <bits/stdc++.h>
using namespace std;

/** Does not work with 0-based indexing */
class fenwick_tree {
  private: 
    int n;
    vector<int> fenw;
    #ifdef DEBUG
    vector<int> debug;
    #endif
  public:
    fenwick_tree() {}

    fenwick_tree(int _n) : n(_n) {
      fenw.assign(n, 0);
      #ifdef DEBUG
      debug.assign(n, 0);
      #endif
    }

    /** Updates fenw[idx] to x. Gets stuck in infinite loop if idx = 0 */
    void update(int idx, int x) {
      #ifdef DEBUG
      debug[idx] += x;
      #endif
      while (idx < n) {
        fenw[idx] += x;
        idx += (idx & -idx);
      }
    }

    /** Returns sum of all elements in fenw[1..idx]. Returns 0 if idx = 0 */
    int query(int idx) {
      int ans = 0;
      while (idx > 0) {
        ans += fenw[idx];
        idx -= (idx & -idx);
      }
      return ans;
    }

    /** Returns smallest idx such that fenw[idx] >= x. Returns n if there is no such element. Assumes all current elements are nonnegative */
    int lower_bound(int x) {
      int idx = 0, cur = 0;
      for (int i = ceil(log2(n + 1)); i >= 0; i--) {
        if (idx + (1 << i) < n && cur + fenw[idx + (1 << i)] < x) {
          idx += (1 << i);
          cur += fenw[idx];
        }
      }
      return idx + 1;
    }
};