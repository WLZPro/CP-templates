#ifndef GRAPHS_CENTROID_DECOMPOSITION_HPP
#define GRAPHS_CENTROID_DECOMPOSITION_HPP 1

#include <bits/stdc++.h>
using namespace std;

class centroid_decomposition {
  private:
    int n;
    vector<int> p, sz;
    vector< set<int> > g;

    int get_sizes(int u, int _p) {
      sz[u] = 1;
      for (auto &v : g[u]) if (v != _p) sz[u] += get_sizes(v, u);
      return sz[u];
    }

    int get_centroid(int u, int _p, int _sz) {
      for (auto &v : g[u]) if (v != _p && sz[v] > _sz / 2) return get_centroid(v, u, _sz);
      return u;
    }

    void build(int u, int _p) {
      int centroid = get_centroid(u, _p, get_sizes(u, _p));
      p[centroid] = _p;
      for (auto &v : g[centroid]) {
        g[v].erase(centroid);
        build(v, centroid);
      }
    }
  public:
    centroid_decomposition(const vector< set<int> > &_g) : g(_g) {
      n = (int) g.size();
      p.assign(n, -1);
      sz.resize(n);
      build(1, -1);
    }

    int operator[](int x) const {
      return p[x];
    }
};

#endif // GRAPHS_CENTROID_DECOMPOSITION_HPP