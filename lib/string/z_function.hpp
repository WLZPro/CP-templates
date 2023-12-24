#pragma once

#include <vector>
#include <string>

// https://cp-algorithms.com/string/z-function.html
template<typename T>
std::vector<int> z_function(const std::basic_string<T> &s) {
    int n = static_cast<int>(s.length());
    std::vector<int> z(n); z[0] = 0;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// https://cp-algorithms.com/string/z-function.html
template<typename T>
std::vector<int> z_function(const std::vector<T> &a) {
    int n = static_cast<int>(a.length());
    std::vector<int> z(n); z[0] = 0;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && a[z[i]] == a[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}