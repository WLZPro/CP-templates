#pragma once

#include <vector>
#include <string>
#include <algorithm>

class union_find {
    public:
    union_find() : n(0) {}
    explicit union_find(int _n) : n(_n), p(n, -1) {}

    int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }

    bool connected(int a, int b) { return root(a) == root(b); }

    int connect(int a, int b) {
        a = root(a); b = root(b);
        if (a == b) return a;
        if (p[a] > p[b]) std::swap(a, b);
        p[a] += p[b]; p[b] = a;
        return a;
    }

    int size() const { return n; }

    int size(int a) { return -p[root(a)]; }

    std::vector< std::vector<int> > groups() {
        std::vector< std::vector<int> > ans(n);
        for (int i = 0; i < n; i++) ans[root(i)].push_back(i);
        ans.erase(std::remove_if(ans.begin(), ans.end(), [](const std::vector<int> &a) { return a.empty(); }), ans.end());
        return ans;
    }

    friend std::string to_string(union_find uf) {
        #ifdef DEBUG
        return to_string(uf.groups());
        #else
        return "";
        #endif
    }

    private:
    int n;
    std::vector<int> p;
};
