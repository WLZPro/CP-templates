#include <bits/stdc++.h>
using namespace std;

const long long INF = (long long) 1e18;

/**
 * @brief Li Chao Tree with dynamically created nodes
 */
class li_chao_tree {
    private:
    struct line { long long m, b; };
    long long eval(const line &f, long long x) { return f.m * x + f.b; }
    struct node {
        node *left, *right;
        line f;
        long long l, r;
        node(long long _l, long long _r) : l(_l), r(_r) {
            left = right = nullptr;
            f = {0, INF};
        }
        } *root;

    void add(node *cur, line nf) {
        long long m = (cur->l + cur->r) / 2;
        bool bl = eval(nf, cur->l) < eval(cur->f, cur->l);
        bool bm = eval(nf, m) < eval(cur->f, m);
        if (bm) swap(cur->f, nf);
        if (cur->r - cur->l == 1) return;
        if (bl != bm) {
            if (cur->left == nullptr) cur->left = new node(cur->l, m);
            add(cur->left, nf);
        } else {
            if (cur->right == nullptr) cur->right = new node(m, cur->r);
            add(cur->right, nf);
        }
    }

    long long query(node *cur, long long x) {
        if (cur == nullptr) return INF;
        if (cur->r - cur->l == 1) return eval(cur->f, x);
        long long m = (cur->l + cur->r) / 2;
        if (x < m) return min(eval(cur->f, x), query(cur->left, x));
        else return min(eval(cur->f, x), query(cur->right, x));
    }

    public:
    li_chao_tree(long long l, long long r) {
        root = new node(l, r);
    }    

    void add(long long m, long long b) {
        add(root, {m, b});
    }

    long long query(long long x) {
        return query(root, x);
    }
};