template<typename T>
struct dinic {
    static constexpr int N = 5005, M = 1.2e5 + 5;
    int n, ei = 0, from[M], to[M], deg[N], g[M], it[N], lvl[N], q[N];
    T cap[N][N], flow[N][N];

    dinic(int _n) : n(_n) { memset(cap, 0, sizeof cap); }

    void add_edge(int u, int v, int c) {
        if (!cap[u][v] || !cap[v][u]) {
            from[ei] = u; to[ei++] = v; 
            from[ei] = v; to[ei++] = u;
        }
        cap[u][v] += c;
    }

    T max_flow(int s, int t, int mxk = 30) {
        memset(deg, 0, sizeof deg);
        memset(flow, 0, sizeof flow);
        rep(i, 0, ei) ++deg[from[i] + 1];
        rep(i, 1, n + 1) deg[i] += deg[i - 1];
        memcpy(it, deg, sizeof deg);
        rep(i, 0, ei) g[it[from[i]]++] = i;

        auto bfs = [&](int k) {
            memset(lvl, -1, sizeof lvl); lvl[s] = 0;
            int qi = 0, qj = 1; q[0] = s;
            while (qi < qj) {
                int u = q[qi++];
                rep(i, deg[u], deg[u + 1]) {
                    int v = to[g[i]];
                    if (((cap[u][v] - flow[u][v]) >> k) && lvl[v] == -1) {
                        q[qj++] = v;
                        lvl[v] = lvl[u] + 1;
                        if (v == t) return;
                    }
                }
            }
        };

        auto dfs = [&](auto &&self, int u, T f) -> T {
            if (u == t || !f) return f;
            T used = 0;
            for (int &i = it[u]; i < deg[u + 1] - deg[u] && used < f; ++i) {
                int v = to[g[deg[u] + i]];
                if (flow[u][v] == cap[u][v] || lvl[v] != lvl[u] + 1) continue;
                T nf = self(self, v, min(f - used, cap[u][v] - flow[u][v]));
                if (!nf) { lvl[v] = -1; continue; }
                flow[u][v] += nf; flow[v][u] -= nf;
                used += nf;
                if (used == f) break;
            }
            return used;
        };

        T ans = 0;
        repr(k, mxk + 1, 0) {
            do {
                bfs(k); memset(it, 0, sizeof it);
                while (T f = dfs(dfs, s, numeric_limits<T>::max())) ans += f;
            } while (lvl[t] != -1);    
        }
        return ans;
    }
};
