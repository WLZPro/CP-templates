#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>

// https://codeforces.com/blog/entry/91632
// Complexity: O(n^(3/4)/(log(n))^(1/2))
template<typename T = uint64_t>
T prime_count(uint64_t n) {
    size_t sq = sqrtl(n);

    std::vector<uint64_t> floors; floors.reserve(2 * sq);
    for (uint64_t k = 1; k <= n; k = n / (n / k) + 1) floors.push_back(n / k);
    std::reverse(floors.begin(), floors.end());

    size_t k = floors.size();
    auto floor_idx = [&](uint64_t m) -> int {
        if (m <= k / 2) return m - 1;
        return k - n / m;
    };
    
    std::vector<T> dp(floors.begin(), floors.end());
    std::vector<uint32_t> pr, spf(sq + 1, 0);
    for (uint32_t m = 2; m <= sq; m++) {
        if (spf[m] == 0) {
            pr.push_back(m);
            spf[m] = m;
            for (int i = k - 1; i >= 0; i--) {
                if (floors[i] < static_cast<uint64_t>(m) * m) break;
                dp[i] -= dp[floor_idx(floors[i] / m)] - static_cast<T>(pr.size());
            }
        }
        for (auto &p : pr) {
            if (p > spf[m] || m * p > sq) break;
            spf[m * p] = p;
        }
    }
    return dp.back() - 1;
}