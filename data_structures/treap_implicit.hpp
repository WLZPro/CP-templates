// https://judge.yosupo.jp/submission/168888

#ifndef DATA_STRUCTURES_TREAP_IMPLICIT_HPP
#define DATA_STRUCTURES_TREAP_IMPLICIT_HPP 1

#include <random>
#include <chrono>
#include <vector>

template<typename T, auto f, typename TMap, auto apply, auto combine, auto id>
class implicit_treap {
    private:
    std::mt19937 rng;

    struct node {
        T val, range_val;
        int pr, cnt;
        TMap lazy;
        bool rev;
        node *l, *r;

        node() {}
        node(const T &_val, const int &_pr) : val(_val), range_val(_val), pr(_pr), cnt(1), lazy(id()), rev(false), l(nullptr), r(nullptr) {}
    } *root;

    #define CNT(t) ((t) == nullptr ? 0 : (t)->cnt)

    inline void push(node *t) {
        if (t == nullptr) return;
        if (t->rev) {
            t->rev = false;
            std::swap(t->l, t->r);
            if (t->l != nullptr) t->l->rev = !t->l->rev;
            if (t->r != nullptr) t->r->rev = !t->r->rev;
        }
        t->val = apply(t->lazy, t->val); t->range_val = apply(t->lazy, t->range_val);
        if (t->l != nullptr) t->l->lazy = combine(t->lazy, t->l->lazy);
        if (t->r != nullptr) t->r->lazy = combine(t->lazy, t->r->lazy);
        t->lazy = id();
    }

    inline void update_from_children(node *t) {
        if (t == nullptr) return;
        if (t->l != nullptr) push(t->l);
        if (t->r != nullptr) push(t->r);
        t->cnt = CNT(t->l) + CNT(t->r) + 1;
        t->range_val = t->val;
        if (t->l != nullptr) t->range_val = f(t->l->range_val, t->range_val);
        if (t->r != nullptr) t->range_val = f(t->range_val, t->r->range_val);
    }

    inline void heapify(node *t) {
        if (t == nullptr) return;
        node *mx_pr = t;
        if (t->l != nullptr && t->l->pr > mx_pr->pr) mx_pr = t->l;
        if (t->r != nullptr && t->r->pr > mx_pr->pr) mx_pr = t->r;
        if (mx_pr != t) {
            std::swap(t->pr, mx_pr->pr);
            heapify(mx_pr);
        }
    }

    node *build(const std::vector<T> &a, int l, int r) {
        if (l >= r) return nullptr;
        int m = (l + r) >> 1;
        node *t = new node(a[m], rng());
        t->l = build(a, l, m); t->r = build(a, m + 1, r);
        heapify(t);
        update_from_children(t);
        return t;
    }

    void split(node *t, node *&l, node *&r, int idx, int add = 0) {
        if (t == nullptr) {
            l = r = nullptr;
            return;
        }
        push(t);
        if (idx <= add + CNT(t->l)) split(t->l, l, t->l, idx, add), r = t;
        else                        split(t->r, t->r, r, idx, add + CNT(t->l) + 1), l = t;
        update_from_children(t);
    }

    void merge(node *&t, node *l, node *r) {
        push(l); push(r);
        if (l == nullptr)      t = r;
        else if (r == nullptr) t = l;
        else if (l->pr > r->pr) merge(l->r, l->r, r), t = l;
        else                    merge(r->l, l, r->l), t = r;
        update_from_children(t);
    }

    T query(node *t, int l, int r, int add = 0) {
        push(t);
        if (l <= add && add + CNT(t) - 1 <= r) return t->range_val;
        bool ans_def = false; T ans{};
        int cur_idx = add + CNT(t->l);
        if (l < cur_idx && t->l != nullptr) ans = query(t->l, l, r, add), ans_def = true;
        if (l <= cur_idx && cur_idx <= r) {
            if (!ans_def) ans = t->val, ans_def = true;
            else ans = f(ans, t->val);
        }
        if (r > cur_idx && t->r != nullptr) {
            if (!ans_def) ans = query(t->r, l, r, cur_idx + 1), ans_def = true;
            else ans = f(ans, query(t->r, l, r, add + CNT(t->l) + 1));
        }
        return ans;
    }

    void update(node *t, int l, int r, const TMap &mp, int add = 0) {
        push(t);
        if (l <= add && add + CNT(t) - 1 <= r) {
            t->lazy = mp;
            push(t);
            return;
        }
        int cur_idx = add + CNT(t->l);
        if (l < cur_idx && t->l != nullptr) update(t->l, l, r, mp, add);
        if (l <= cur_idx && cur_idx <= r) t->val = apply(mp, t->val);
        if (r > cur_idx && t->r != nullptr) update(t->r, l, r, mp, cur_idx + 1);
        update_from_children(t);
    }

    void erase(node *&t, int idx, int add = 0) {
        push(t);
        int cur_idx = add + CNT(t->l);
        if (cur_idx == idx) {
            node *rm = t;
            merge(t, t->l, t->r);
            delete rm;
        } else if (idx < cur_idx) erase(t->l, idx, add);
          else                    erase(t->r, idx, add + CNT(t->l) + 1);
        update_from_children(t);
    }

    void destroy(node *t) {
        if (t == nullptr) return;
        if (t->l != nullptr) destroy(t->l);
        if (t->r != nullptr) destroy(t->r);
        delete t;
    }

    #undef CNT

    public:
    implicit_treap() : implicit_treap(std::vector<T>(), std::chrono::steady_clock().now().time_since_epoch().count()) {}

    explicit implicit_treap(const std::vector<T> &a) : implicit_treap(a, std::chrono::steady_clock().now().time_since_epoch().count()) {}

    implicit_treap(const std::vector<T> &a, const int &seed) {
        rng.seed(seed);
        root = build(a, 0, static_cast<int>(a.size()));
    }

    ~implicit_treap() { destroy(root); }

    void insert(int idx, const T &val) {
        node *t_r;
        split(root, root, t_r, idx);
        merge(root, root, new node(val, rng())); merge(root, root, t_r);
    }

    T query(int l, int r) { return query(root, l, r); }

    void update(int l, int r, const TMap &mp) { update(root, l, r, mp); }

    void erase(int idx) { erase(root, idx); }

    void reverse(int l, int r) {
        node *t_l, *t_r;
        split(root, t_l, root, l); split(root, root, t_r, r - l + 1);
        root->rev = !root->rev;
        merge(root, t_l, root); merge(root, root, t_r);
    }

    T operator[](int idx) { return query(idx, idx); }

    int size() const { return root->cnt; }
};

#endif // DATA_STRUCTURES_TREAP_IMPLICIT_HPP