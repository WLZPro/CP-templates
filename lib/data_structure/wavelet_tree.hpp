#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
struct wavelet_tree {
    public:

    wavelet_tree(const std::vector<T> &_a) 
     : n(static_cast<int>(_a.size())), sz(1 << (__lg(n) + 1)), a(_a), ord(n), pre(__lg(n) + 1, std::vector<int>(n, 0)) {

        std::vector<int> b(n), c(n);
        std::iota(b.begin(), b.end(), 0);
        std::sort(b.begin(), b.end(), [&](int i, int j) {
            if (a[i] == a[j]) return i < j;
            return a[i] < a[j];
        });

        std::iota(ord.begin(), ord.end(), 0);

        for (int k = 0, len = sz; len > 1; len >>= 1, k++) {
            for (int cl = 0; cl < n; cl += len) {
                int cr = std::min(n, cl + len), cm = std::min(n, cl + (len >> 1));
                int l = cl, r = cm;
                for (int i = cl; i < cr; i++) {
                    if (i > cl) pre[k][i] = pre[k][i - 1];
                    if (cm == n || a[ord[i]] < a[b[cm]] || (a[ord[i]] == a[b[cm]] && ord[i] < b[cm])) c[l++] = ord[i], pre[k][i]++;
                    else c[r++] = ord[i];
                }
            }
            ord.swap(c);
        }
    }

    T find_by_order(int l, int r, int k) {
        r++;
        int cl = 0, lvl = 0;
        for (int len = sz >> 1; len >= 1; lvl++, len >>= 1) {
            int cm = std::min(cl + len, n);
            int cnt_l = l > 0 ? pre[lvl][cl + l - 1] : 0, cnt_r = pre[lvl][cl + r - 1];
            if (k < cnt_r - cnt_l) {
                l = cnt_l; r = cnt_r;
            } else {
                cl = cm;
                k -= cnt_r - cnt_l;
                l -= cnt_l; r -= cnt_r;
            }
        }
        return a[ord[cl]];
    }

    private:
    int n, sz;
    std::vector<T> a;
    std::vector<int> ord;
    std::vector< std::vector<int> > pre;
};