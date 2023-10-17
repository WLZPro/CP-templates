#ifndef DYNAMIC_PROGRAMMING_DIVIDE_AND_CONQUER_DP_HPP
#define DYNAMIC_PROGRAMMING_DIVIDE_AND_CONQUER_DP_HPP 1

#include <vector>
#include <functional>

// Iterative Divide and Conquer DP implementation,
// based on [this article](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html).
// Tested on [Codeforces 321E](https://codeforces.com/contest/321/problem/E).
// @note For some reason, this iterative implementation is slower than a recursive implementation.
namespace dnc_dp {

    template<typename T>
    T calc_dp(int rows, int cols, const std::function<T(int, int)> &cost) {
        std::vector<int> l(cols), r(cols); l[0] = 0; r[0] = cols - 1;
        for (int j = 0, idx = 1; j < cols; j++) {
            int m = (l[j] + r[j]) >> 1;
            if (l[j] <= m - 1) l[idx] = l[j], r[idx++] = m - 1;
            if (m + 1 <= r[j]) l[idx] = m + 1, r[idx++] = r[j];
        }
        std::vector dp(2, std::vector<T>(cols));
        for (int j = 0; j < cols; j++) dp[0][j] = cost(0, j);
        std::vector<int> cl(cols), cr(cols); cl[0] = 0; cr[0] = cols - 1;
        for (int i = 1, cur = 1; i < rows; i++, cur = (cur + 1) & 1) {
            for (int j = 0, idx = 1; j < cols; j++) {
                int m = (l[j] + r[j]) >> 1, cm = cl[j];
                dp[cur][m] = (cl[j] > 0 ? dp[!cur][cl[j] - 1] : 0) + cost(cl[j], m);
                for (int k = cl[j] + 1; k <= m && k <= cr[j]; k++) {
                    T tmp = dp[!cur][k - 1] + cost(k, m);
                    if (tmp < dp[cur][m]) dp[cur][m] = tmp, cm = k;
                }
                if (l[j] <= m - 1) cl[idx] = cl[j], cr[idx++] = cm;
                if (m + 1 <= r[j]) cl[idx] = cm, cr[idx++] = cr[j];
            }
        }
        return dp[(rows - 1) % 2][cols - 1];
    }

} // namespace dnc_dp

#endif // DYNAMIC_PROGRAMMING_DIVIDE_AND_CONQUER_DP_HPP