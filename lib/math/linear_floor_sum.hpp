#pragma once

// https://codeforces.com/blog/entry/97562?#comment-864528
template<typename T>
T linear_floor_sum(const T &n, const T &m, const T &a, const T &b) {
    if (n <= 8) {
        T ans{0};
        for (int i = 0; i < n; i++) ans += (a * i + b) / m;
        return ans;
    }
    if (a >= m) return (a / m) * n * (n - 1) / 2 + linear_floor_sum(n, m, a % m, b);
    if (b >= m) return (b / m) * n + linear_floor_sum(n, m, a, b % m);
    T tmp = (a * (n - 1) + b) / m;
    return (n - 1) * tmp - linear_floor_sum(tmp, a, m, m - b - 1);
}