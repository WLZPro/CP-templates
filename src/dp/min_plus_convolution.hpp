#pragma once

#include <vector>

// Assumptions: `a` and `b` are convex and nonempty
template<typename T>
std::vector<T> convex_convex_min_plus_conv(const std::vector<T> &a, const std::vector<T> &b) {
    int n = static_cast<int>(a.size()), m = static_cast<int>(b.size());
    std::vector<T> ans(n + m - 1); ans[0] = a[0] + b[0];
    for (int i = 0, j = 0; i < n - 1 || j < m - 1; ) {
        if (j == m - 1 || (i < n - 1 && a[i + 1] - a[i] < b[j + 1] - b[j])) i++, ans[i + j] = a[i] - a[i - 1];
        else j++, ans[i + j] = b[j] - b[j - 1];
        ans[i + j] += ans[i + j - 1];
    }
    return ans;
}