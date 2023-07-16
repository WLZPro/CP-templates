#include <bits/stdc++.h>
using namespace std;

/** 1-indexed LCA class */
class least_common_ancestor {
  private:
    int n, max_log, dfs_cnt = 0, root;
    vector< vector< pair<int, int> > > g;
    vector< vector<int> > up;
    vector<int> d, dfs_in, dfs_out;

    void dfs(int u, int p) {
      dfs_in[u] = dfs_cnt++;
      up[u][0] = p;
      for (int i = 1; i <= max_log; i++) up[u][i] = up[up[u][i - 1]][i - 1];
      for (auto &v : g[u]) {
        if (v.first == u) continue;
        d[v.first] = d[u] + v.second;
        dfs(v.first, u);
      }
      dfs_out[u] = dfs_cnt;
    }

    void init() {
      n = (int) g.size() - 1;
      max_log = ceil(log2(n + 1));
      up.assign(n + 1, vector<int>(max_log + 1));
      d.assign(n + 1, 0);
      dfs_in.resize(n + 1);
      dfs_out.resize(n + 1);
      dfs(root, root);
    }
  public:

    /** Assigns weight 1 to all edges in an unweighted tree */
    least_common_ancestor(const vector< vector<int> > &_g, int _root = 1) : root(_root) {
      g.assign((int) _g.size(), vector< pair<int, int> >());
      for (int i = 0; i < (int) _g.size(); i++) {
        for (auto &x : _g[i]) g[i].emplace_back(x, 1);
      }
      init();
    }

    bool is_anc(int u, int v) {
      return dfs_in[u] <= dfs_in[v] && dfs_out[v] <= dfs_out[u];
    }

    int query(int u, int v) {
      if (is_anc(u, v)) return u;
      if (is_anc(v, u)) return v;
      for (int i = max_log; i >= 0; i--) {
        if (!is_anc(up[u][i], v)) u = up[u][i];
      }
      return up[u][0];
    }

    int preorder(int u) {
      return dfs_in[u];
    }
};