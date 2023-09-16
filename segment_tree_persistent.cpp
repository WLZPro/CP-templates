#include <bits/stdc++.h>
using namespace std;

/* 
Persistent segment tree
Query returns maximum along with index of maximal element (smallest index in case of ties)
Supports point add updates
*/ 

struct node {
    int l, r, val, idx;
    node *left, *right;
};

node *build(int l, int r) {
    if (l == r) return new node{l, r, 0, -l, nullptr, nullptr};
    node *left = build(l, (l + r) / 2), *right = build((l + r) / 2 + 1, r);
    return new node{l, r, 0, -l, left, right};
}

pair<int, int> query(node *cur, int l, int r) {
    if (cur->l >= l && cur->r <= r) return {cur->val, cur->idx};
    if (cur->l > r || cur->r < l) return {0, 0};
    auto left = query(cur->left, l, r), right = query(cur->right, l, r);
    return max(left, right);
}

node *update(node *cur, int idx, int val) {
    if (cur->l == cur->r) return new node{idx, idx, cur->val + val, cur->idx, nullptr, nullptr};
    node *ans = new node{cur->l, cur->r, cur->val, cur->idx, cur->left, cur->right};
    if (idx <= cur->left->r) ans->left = update(cur->left, idx, val);
    else ans->right = update(cur->right, idx, val);
    tie(ans->val, ans->idx) = max(make_pair(ans->left->val, ans->left->idx), make_pair(ans->right->val, ans->right->idx));
    return ans;
}