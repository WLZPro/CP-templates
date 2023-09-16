#include <bits/stdc++.h>
using namespace std;

class dsu {
  private: vector<int> p, rank, sz;
  public:
    dsu(int n) {
        p.assign(n, -1);
        rank.assign(n, 0);
        sz.assign(n, 1);
    }

    int root(int x) {
        if (p[x] == -1) return x;
        return p[x] = root(p[x]);
    }

    bool connected(int x, int y) {
        return root(x) == root(y);
    }

    void connect(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
            if (rank[x] > rank[y]) p[y] = x, sz[x] += sz[y];
            else {
            p[x] = y;
            sz[y] += sz[x];
            if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }

    int size(int x) {
        return sz[root(x)];
    }
};