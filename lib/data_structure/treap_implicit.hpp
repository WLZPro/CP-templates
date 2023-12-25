#pragma once

#include "util/abstract_types.hpp"

#include <random>
#include <chrono>
#include <vector>

// https://cp-algorithms.com/data_structures/treap.html
template<typename _Mn, typename _Hm = id_map<typename _Mn::T>, int cache_size = 1 << 20>
class implicit_treap {
    using T = typename _Mn::T;
    using F = typename _Hm::T;

    public:
    using value_type = T;
    using mapping_type = F;

    implicit_treap() : implicit_treap(std::vector<T>(), std::chrono::steady_clock().now().time_since_epoch().count()) {}

    explicit implicit_treap(const std::vector<T> &a) : implicit_treap(a, std::chrono::steady_clock().now().time_since_epoch().count()) {}

    implicit_treap(const std::vector<T> &a, const int &seed) {
        rng.seed(seed);
        root = build(a, 0, static_cast<int>(a.size()));
    }

    void insert(int idx, const T &val) {
        node *t_r;
        split(root, root, t_r, idx);
        merge(root, root, fetch(val, rng())); merge(root, root, t_r);
    }

    T query(int l, int r) { return query(root, l, r); }

    void update(int l, int r, const F &f) { update(root, l, r, f); }

    void erase(int idx) { erase(root, idx); }

    void reverse(int l, int r) {
        node *t_l, *t_r;
        split(root, t_l, root, l); split(root, root, t_r, r - l + 1);
        root->rev = !root->rev;
        merge(root, t_l, root); merge(root, root, t_r);
    }

    T operator[](int idx) { return query(idx, idx); }

    int size() const { return root->cnt; }
    
    private:
    std::mt19937 rng;

    struct node {
        T val, range_val;
        int pr, cnt;
        F lazy;
        bool has_lazy, rev;
        node *l, *r;
    } cache[cache_size], *root;

    int cache_idx = 0;
    node *fetch(const T &val, const int &pr) {
        node *r = &cache[cache_idx++];
        r->val = r->range_val = val;
        r->pr = pr; r->cnt = 1;
        r->has_lazy = r->rev = false;
        r->l = r->r = nullptr;
        return r;
    }

    int cnt(node *t) { return t == nullptr ? 0 : t->cnt; }

    void push(node *t) {
        if (t == nullptr) return;
        if (t->rev) {
            t->rev = false;
            std::swap(t->l, t->r);
            if (t->l != nullptr) t->l->rev = !t->l->rev;
            if (t->r != nullptr) t->r->rev = !t->r->rev;
        }
        if (!t->has_lazy) return;
        t->val = _Hm::map(t->lazy, t->val);
        if constexpr (has_map_with_implicit_size_v<_Hm>) t->range_val = _Hm::map(t->lazy, t->range_val, cnt(t));
        else t->range_val = _Hm::map(t->lazy, t->range_val);
        if (t->l != nullptr) {
            if (t->l->has_lazy) t->l->lazy = _Hm::comp(t->lazy, t->l->lazy);
            else t->l->lazy = t->lazy, t->l->has_lazy = true;
        }
        if (t->r != nullptr) {
            if (t->r->has_lazy) t->r->lazy = _Hm::comp(t->lazy, t->r->lazy);
            else t->r->lazy = t->lazy, t->r->has_lazy = true;
        }
        t->has_lazy = false;
    }

    void pull(node *t) {
        if (t == nullptr) return;
        if (t->l != nullptr) push(t->l);
        if (t->r != nullptr) push(t->r);
        t->cnt = cnt(t->l) + cnt(t->r) + 1;
        t->range_val = t->val;
        if (t->l != nullptr) t->range_val = _Mn::op(t->l->range_val, t->range_val);
        if (t->r != nullptr) t->range_val = _Mn::op(t->range_val, t->r->range_val);
    }

    void heapify(node *t) {
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
        node *t = fetch(a[m], rng());
        t->l = build(a, l, m); t->r = build(a, m + 1, r);
        heapify(t);
        pull(t);
        return t;
    }

    void split(node *t, node *&l, node *&r, int idx, int add = 0) {
        if (t == nullptr) {
            l = r = nullptr;
            return;
        }
        push(t);
        if (idx <= add + cnt(t->l)) split(t->l, l, t->l, idx, add), r = t;
        else                        split(t->r, t->r, r, idx, add + cnt(t->l) + 1), l = t;
        pull(t);
    }

    void merge(node *&t, node *l, node *r) {
        push(l); push(r);
        if (l == nullptr)      t = r;
        else if (r == nullptr) t = l;
        else if (l->pr > r->pr) merge(l->r, l->r, r), t = l;
        else                    merge(r->l, l, r->l), t = r;
        pull(t);
    }

    T query(node *t, int l, int r, int add = 0) {
        push(t);
        if (l <= add && add + cnt(t) - 1 <= r) return t->range_val;
        bool ans_def = false; T ans{};
        int cur_idx = add + cnt(t->l);
        if (l < cur_idx && t->l != nullptr) ans = query(t->l, l, r, add), ans_def = true;
        if (l <= cur_idx && cur_idx <= r) {
            if (!ans_def) ans = t->val, ans_def = true;
            else ans = _Mn::op(ans, t->val);
        }
        if (r > cur_idx && t->r != nullptr) {
            if (!ans_def) ans = query(t->r, l, r, cur_idx + 1), ans_def = true;
            else ans = _Mn::op(ans, query(t->r, l, r, add + cnt(t->l) + 1));
        }
        return ans;
    }

    void update(node *t, int l, int r, const F &f, int add = 0) {
        push(t);
        if (l <= add && add + cnt(t) - 1 <= r) {
            t->has_lazy = true; t->lazy = f;
            push(t);
            return;
        }
        int cur_idx = add + cnt(t->l);
        if (l < cur_idx && t->l != nullptr) update(t->l, l, r, f, add);
        if (l <= cur_idx && cur_idx <= r) t->val = _Hm::map(f, t->val);
        if (r > cur_idx && t->r != nullptr) update(t->r, l, r, f, cur_idx + 1);
        pull(t);
    }

    void erase(node *&t, int idx, int add = 0) {
        push(t);
        int cur_idx = add + cnt(t->l);
        if (cur_idx == idx) merge(t, t->l, t->r);
        else if (idx < cur_idx) erase(t->l, idx, add);
        else                    erase(t->r, idx, add + cnt(t->l) + 1);
        pull(t);
    }
};