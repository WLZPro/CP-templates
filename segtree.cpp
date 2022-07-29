struct node {
  int l, r, val, lazy;
  node *left ,*right;
};

node *build(int l, int r) {
  if (l == r) return new node{l, r, 0, 0, nullptr, nullptr};
  node *left = build(l, (l + r) / 2), *right = build((l + r) / 2 + 1, r);
  return new node{l, r, 0, 0, left, right};
}

void propagate(node *cur) {
  if (cur->lazy == 0) return;
  cur->val += cur->lazy;
  if (cur->left != nullptr) {
    cur->left->lazy += cur->lazy;
    cur->right->lazy += cur->lazy;
  }
  cur->lazy = 0;
}

int query(node *cur, int l, int r) { // min
  propagate(cur);
  if (l > cur->r || r < cur->l) return INF;
  if (l <= cur->l && cur->r <= r) return cur->val;
  return min(query(cur->left, l, r), query(cur->right, l, r));
}

void update(node *cur, int l, int r, int val) { // add
  propagate(cur);
  if (l > cur->r || r < cur->l) return;
  if (l <= cur->l && cur->r <= r) {
    cur->lazy += val;
    propagate(cur);
    return;
  }
  update(cur->left, l, r, val); update(cur->right, l, r, val);
  cur->val = min(cur->left->val, cur->right->val);
}