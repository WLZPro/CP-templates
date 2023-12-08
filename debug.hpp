#ifndef DEBUG_HPP
#define DEBUG_HPP 1

#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <complex>

using std::to_string;

// Copied from tourist

#define debug(...) std::cerr << "[DEBUG]: " << __FILE__ << ':' << __LINE__ << ": " << "[" << #__VA_ARGS__ << "]: [", debug_out(__VA_ARGS__)

std::string to_string(const std::string &s) { return '"' + s + '"'; }

std::string to_string(const char *s) { return to_string(std::string(s)); }

std::string to_string(bool b) { return (b ? "true" : "false"); }

template <typename T1, typename T2>
std::string to_string(std::pair<T1, T2> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

template<typename T>
std::string to_string(const std::priority_queue<T> &pq) {
    std::priority_queue<T> tmp = pq;
    std::string ans = "{";
    bool first = true;
    while (!tmp.empty()) {
        if (!first) ans += ", ";
        first = false;
        ans += to_string(tmp.top());
        tmp.pop();
    }
    ans += '}';
    return ans;
}

template<typename T>
std::string to_string(const std::stack<T> &st) {
    std::stack<T> tmp = st;
    std::string ans = "{";
    bool first = true;
    while (!tmp.empty()) {
        if (!first) ans += ", ";
        first = false;
        ans += to_string(tmp.top());
        tmp.pop();
    }
    ans += '}';
    return ans;
}

template<typename T>
std::string to_string(const std::queue<T> &q) {
    std::queue<T> tmp = q;
    std::string ans = "{";
    bool first = true;
    while (!tmp.empty()) {
        if (!first) ans += ", ";
        first = false;
        ans += to_string(tmp.front());
        tmp.pop();
    }
    ans += '}';
    return ans;
}

template<typename T>
std::string to_string(const std::complex<T> &z) {
    std::string ans = to_string(z.real());
    if (z.imag() > 0) ans += '+' + to_string(z.imag());
    else ans += '-' + to_string(-z.imag());
    ans += 'i';
    return ans;
}

template<typename T>
std::string to_string(const T &v) {
    bool first = true;
    std::string ans = "{";
    for (const auto &x : v) {
        if (!first) ans += ", ";
        first = false;
        ans += to_string(x);
    }
    ans += "}";
    return ans;
}

void debug_out() { std::cerr << "[]" << std::endl; }

template<typename Head>
void debug_out(const Head &H) {
    std::cerr << to_string(H) << ']' << std::endl;
}

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << to_string(H) << ", ";
    debug_out(T...);
}

#endif // DEBUG_HPP