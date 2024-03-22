#pragma once

#include "util/abstract_types.hpp"

#include <vector>
#include <utility>

template<typename M, typename H = id_map<typename M::T> >
class implicit_splay_tree {
    using T = typename M::T;
    using F = typename H::T;

    public:
    using value_type = T;
    using mapping_type = F;

    implicit_splay_tree() {}

    implicit_splay_tree(const std::vector<T> &a) {
        auto build = [&a](auto &&self, int l, int r) -> node* {
            if (l >= r) return 0;
            int m = (l + r) / 2;
            node *nw = new node(a[m]);
            if ((nw->c[0] = self(self, l, m))) nw->c[0]->p = nw;
            if ((nw->c[1] = self(self, m + 1, r))) nw->c[1]->p = nw;
            nw->pull();
            return nw;
        };
        root = build(build, 0, a.size());
    }

    void insert(int i, const T &v) {
        if (!root) {
            root = new node(v);
            return;
        }
        node *t = root; t->push();
        bool s = i > cnt(t->c[0]);
        for (; t->c[s]; s = i > cnt(t->c[0])) {
            if (s) i -= cnt(t->c[0]) + 1;
            t = t->c[s]; t->push();
        }
        node *nw = new node(v, t);
        t->c[s] = nw; nw->splay(); root = nw;
    }

    void erase(int i) { erase(i, i); }

    void erase(int l, int r) {
        node *t = find_range(l, r);
        if (t->p) {
            t->p->c[t->side()] = 0;
            t->p->pull();
            if (t->p->p) t->p->p->pull();
        }
    }

    // const T &query(int i) {
    //     node *t = find(i);
    //     t->splay(); root = t;
    //     return t->v;
    // }

    const T &query(int l, int r) {
        node *t = find_range(l, r);
        t->push();
        return t->rv;
    }

    const T &operator[](int i) { return query(i, i); }

    void update(int l, int r, const F &f) {
        node *t = find_range(l, r);
        if (t->hlz) t->lz = H::comp(f, t->lz);
        else t->lz = f, t->hlz = 1;
        t->push();
        if (t->p) {
            t->p->pull();
            if (t->p->p) t->p->p->pull();
        }
    }

    // Only works if `G::op` is commutative
    void reverse(int l, int r) {
        node *t = find_range(l, r);
        t->rev ^= 1;
    }

    int size() const { return cnt(root); }

    private:
    struct node {
        node *c[2], *p;
        T v, rv; int cnt;
        F lz;
        bool hlz, rev;

        node(const T &_v, node *_p = 0)
         : c{0, 0}, p(_p), v(_v), rv(_v), cnt(1), hlz(0), rev(0) {}

        inline void push() {
            if (rev) std::swap(c[0], c[1]);
            if (hlz) {
                v = H::map(lz, v);
                if constexpr (has_map_with_implicit_size_v<H>) rv = H::map(lz, rv, cnt);
                else rv = H::map(lz, rv);
            }
            for (int i = 0; i < 2; ++i) if (c[i]) {
                c[i]->rev ^= rev;
                if (hlz) {
                    if (c[i]->hlz) c[i]->lz = H::comp(lz, c[i]->lz);
                    else c[i]->lz = lz, c[i]->hlz = 1;
                }
            }
            hlz = rev = 0;
        }

        inline void pull() {
            cnt = 1; rv = v;
            if (c[0]) c[0]->push(), cnt += c[0]->cnt, rv = M::op(c[0]->rv, rv);
            if (c[1]) c[1]->push(), cnt += c[1]->cnt, rv = M::op(rv, c[1]->rv);
        }

        inline bool side() const { return this == p->c[1]; }

        inline void rot() {
            bool s = side();
            if (c[!s]) c[!s]->p = p;
            p->c[s] = std::exchange(c[!s], p);
            p->pull(); pull();
            if (p->p) p->p->c[p->side()] = this;
            p = std::exchange(p->p, this);
        }

        void splay(node *u = 0) {
            while (p != u) {
                if (p->p != u) {
                    if (side() == p->side()) p->rot();
                    else rot();
                }
                rot();
            }
        }
    } *root = 0;

    inline int cnt(node *t) { return t ? t->cnt : 0; }

    node *find(int i) {
        for (node *t = root; t; ) {
            t->push();
            if (i == cnt(t->c[0])) return t;
            if (i < cnt(t->c[0])) t = t->c[0];
            else i -= cnt(t->c[0]) + 1, t = t->c[1];
        }
        return 0;
    }

    node *find_range(int l, int r) {
        node *tl = find(l - 1), *tr = find(r + 1);
        if (!tl && !tr) return root;
        if (tr) tr->splay(), root = tr;
        if (tl) {
            tl->splay(tr);
            if (!tr) root = tl;
            return tl->c[1];
        } else return tr->c[0];
    }
};