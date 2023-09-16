#include <bits/stdc++.h>
using namespace std;

template<typename T> void cmax(T &a, const T &b) { a = max(a, b); }
template<typename T> void cmin(T &a, const T &b) { a = min(a, b); }

const int INF = 0x3f3f3f3f;

/**
 * @brief Segment tree with dynamically created nodes
 * 
 */
struct node {
    int l, r, val, lazy;
    node *left ,*right;
};

node *build(int l, int r) {
    return new node{l, r, -INF, -INF, nullptr, nullptr};
}

void propagate(node *cur) {
    if (cur == nullptr || cur->lazy == -INF) return;
    cmax(cur->val, cur->lazy);
    if (cur->l != cur->r) {
        if (cur->left == nullptr) cur->left = build(cur->l, (cur->l + cur->r) / 2);
        if (cur->right == nullptr) cur->right = build((cur->l + cur->r) / 2 + 1, cur->r);
        cmax(cur->left->lazy, cur->lazy);
        cmax(cur->right->lazy, cur->lazy);
    }
    cur->lazy = -INF;
}

int query(node *cur, int l, int r) { // max
    if (cur == nullptr) return -INF;
    propagate(cur);
    if (l > cur->r || r < cur->l) return -INF;
    if (l <= cur->l && cur->r <= r) return cur->val;
    return max(query(cur->left, l, r), query(cur->right, l, r));
}

void update(node *cur, int l, int r, int val) { // add
    propagate(cur);
    if (l > cur->r || r < cur->l) return;
    if (l <= cur->l && cur->r <= r) {
        cmax(cur->lazy, val);
        propagate(cur);
        return;
    }
    if (cur->left == nullptr) cur->left = build(cur->l, (cur->l + cur->r) / 2);
    if (cur->right == nullptr) cur->right = build((cur->l + cur->r) / 2 + 1, cur->r);
    update(cur->left, l, r, val); update(cur->right, l, r, val);
    cur->val = max(cur->left->val, cur->right->val);
}