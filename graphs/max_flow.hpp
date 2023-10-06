#include "graphs.hpp"

#include <queue>
#include <limits>

namespace graphs {

// Tested on https://cses.fi/problemset/task/1694/
template<typename T>
T max_flow(const graph<T> &g, unsigned int s, unsigned int t) {
    std::size_t n = g.size();
    std::vector< std::vector<T> > cap(n, std::vector<T>(n, 0));
    graph tg(n);
    for (auto &[from, to, w] : g.edges()) {
        cap[from][to] += w;
        tg.add_edge(from, to); tg.add_edge(to, from);
    }
    T flow = 0;
    std::vector<unsigned int> p(n);

    auto bfs = [&]() {
        p.assign(n, n); p[s] = n + 1;
        std::queue< std::pair<unsigned int, T> > q; q.emplace(s, std::numeric_limits<T>::max());
        while (!q.empty()) {
            auto [from, flow] = q.front(); q.pop();
            for (auto &[to, w] : tg[from]) {
                if (p[to] == n && cap[from][to]) {
                    p[to] = from;
                    T nf = std::min(flow, cap[from][to]);
                    if (to == t) return nf;
                    q.emplace(to, nf);
                }
            }
        }
        return (T) 0;
    };

    for (T nf; (nf = bfs()); ) {
        flow += nf;
        unsigned int cur = t;
        while (cur != s) {
            unsigned int prev = p[cur];
            cap[prev][cur] -= nf; cap[cur][prev] += nf;
            cur = prev;
        }
    }
    return flow;
}

}