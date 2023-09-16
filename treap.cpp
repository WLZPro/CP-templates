#include <bits/stdc++.h>
using namespace std;

/** No duplicate elements allowed */
class treap {
    private:
    struct node {
        int key, pr, sz;
        node *left, *right;
        node() {}
        node(int _key) : key(_key), pr(rand()), sz(1), left(nullptr), right(nullptr) {}
        node(int _key, int _pr) : key(_key), pr(_pr), sz(1), left(nullptr), right(nullptr) {}
    } *root;

    int sz(node *cur) {
        if (cur == nullptr) return 0;
        return cur->sz;
    }

    void update_sz(node *cur) {
        if (cur != nullptr) cur->sz = sz(cur->left) + sz(cur->right) + 1;
    }

    void split(node *cur, int x, node *&l, node *&r) {
        if (cur == nullptr) l = r = nullptr;      
        else if (cur->key <= x) {
            split(cur->right, x, cur->right, r);
            l = cur;
        } else {
            split(cur->left, x, l, cur->left);
            r = cur;
        }
        update_sz(cur);
    }

    void merge(node *l, node *r, node *&ans) {
        if (l == nullptr) ans = r;
        else if (r == nullptr) ans = l;
        else if (l->pr > r->pr) {
            merge(l->right, r, l->right);
            ans = l;
        } else {
            merge(l, r->left, r->left);
            ans = r;
        }
        update_sz(ans);
    }

    int lower_bound(node *cur, int x) {
        if (cur == nullptr) return 0;
        else if (cur->key == x) return sz(cur->left);
        else if (x < cur->key) return lower_bound(cur->left, x);
        else return 1 + sz(cur->left) + lower_bound(cur->right, x);
    }

    int kth_element(node *cur, int k) {
        if (cur == nullptr) return -1;
        int l_sz = sz(cur->left);
        if (l_sz == k) return cur->key;
        else if (k < l_sz) return kth_element(cur->left, k);
        else return kth_element(cur->right, k - l_sz - 1);
    }

    int count(node *cur, int x) {
        if (cur == nullptr) return 0;
        else if (cur->key == x) return 1;
        else if (x < cur->key) return count(cur->left, x);
        else return count(cur->right, x);
    }

    public:
    treap() {
        root = nullptr;
    }

    void insert(int x) {
        node *added = new node(x), *l, *r;
        split(root, x, l, r);
        merge(l, added, root);
        merge(root, r, root);
    }

    void erase(int x) {
        node *l, *r;
        split(root, x - 1, l, root);
        split(root, x, root, r);
        node *tmp = root;
        merge(l, r, root);
        if (tmp != nullptr) delete tmp;
    }

    /** Returns number of elements strictly less than x */
    int lower_bound(int x) {
        return lower_bound(root, x);
    }

    int count(int x) {
        return count(root, x);
    }

    /** Returns kth largest element. -1 if there are not enough elements */
    int kth_element(int k) {
        return kth_element(root, k);
    }

    size_t size() {
        return (size_t) sz(root);
    }
};