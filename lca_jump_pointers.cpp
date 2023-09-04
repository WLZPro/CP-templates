#include <bits/stdc++.h>
using namespace std;

/**
 * @brief LCA with jump pointers (uses linear memory)
 */
class lowest_common_ancestor {
  private:
    int n;
    vector< vector<int> > g;
    vector<int> p, jump, d;

    void dfs(int u) {
      if (d[p[u]] - d[jump[p[u]]] == d[jump[p[u]]] - d[jump[jump[p[u]]]]) jump[u] = jump[jump[p[u]]];
      else jump[u] = p[u];
      for (auto &v : g[u]) {
        if (v != p[u]) {
          d[v] = d[u] + 1;
          p[v] = u;
          dfs(v);
        }
      }
    }
  public:
    least_common_ancestor(const vector< vector<int> > &_g, int root = 1) : g(_g) {
      n = (int) g.size();
      p.resize(n); jump.resize(n); d.resize(n);
      p[root] = root; jump[root] = root; d[root] = 0;
      dfs(root);
    }
  
    int kth_ancestor(int u, int k) {
      int v = u;
      while (d[v] > d[u] - k) {
        if (d[jump[v]] >= d[u] - k) v = jump[v];
        else v = p[v];
      }
      return v;
    }

    int query(int u, int v) {
      if (d[u] < d[v]) swap(u, v);
      u = kth_ancestor(u, d[u] - d[v]);
      if (u == v) return u;
      while (p[u] != p[v]) {
        if (jump[u] != jump[v]) u = jump[u], v = jump[v];
        else u = p[u], v = p[v];
      }
      return p[u];
    }

    int depth(int u) {
      return d[u];
    }

    int dist(int u, int v) {
      return d[u] + d[v] - 2 * d[query(u, v)];
    }
};
