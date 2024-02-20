// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/FenwickTree.h
struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
};

struct CDQ {
    int my;
    struct query { int x, y; ll z; int i, sgn; };
    vector<query> q;

    CDQ(int _my) : my(_my) {}

    void update(int x, int y, ll val) { // a[x][y] += val
        q.push_back({x, y, val, -1, 0});
    }

    int qi = 0;
    void query(int lx, int rx, int ly, int ry) { // a[lx..rx-1][ly..ry-1]
        if (lx) q.push_back({lx - 1, ly, ry, qi, -1});
        q.push_back({rx - 1, ly, ry, qi++, +1});
    }

    void solve(vector<ll> &ans) {
        int n = SZ(q);
        FT ft(my + 5);
        ans.assign(qi, 0);
        for (int k = 1; k < n; k += k) {
            auto sq(q);
            for (int l = 0; l < n - k; l += k * 2) {
                int m = l + k, r = min(n, l + k * 2), i = l, j = m, p = l;
                while (i < m || j < r) {
                    if (j == r || (i < m && q[i].x <= q[j].x)) {
                        if (!q[i].sgn)
                            ft.update(q[i].y, +q[i].z);
                        sq[p++] = q[i++];
                    } else {
                        if (q[j].sgn)
                            ans[q[j].i] += q[j].sgn * (ft.query(q[j].z) - ft.query(q[j].y));
                        sq[p++] = q[j++];
                    }
                }
                for (i = l; i < m; i++)
                    if (!q[i].sgn)
                        ft.update(q[i].y, -q[i].z);
            }
            q = sq;
        }
    }
};

// https://judge.yosupo.jp/submission/181505