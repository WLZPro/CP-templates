#pragma once

#include <cstdio>
#include <cstdint>
#include <cassert>
#include <string>
#include <type_traits>

namespace std {

namespace fast_io {

constexpr int IN_BUF_SZ = 1 << 17;
char in_buf[IN_BUF_SZ];

size_t in_ptr = 0, in_len = 0;
inline char rd() {
    if (in_ptr == in_len) in_ptr = 0, in_len = fread(in_buf, 1, IN_BUF_SZ, stdin);
    return in_buf[in_ptr++];
}

struct fast_reader { void tie(int *) {} };

inline fast_reader &operator>>(fast_reader &in, char &c) { c = rd(); return in; }

template<typename T, enable_if_t<((is_integral_v<T> && !is_same_v<T, char>)
    || is_same_v<T, __int128_t> || is_same_v<T, __uint128_t>)>* = nullptr>
inline fast_reader &operator>>(fast_reader &in, T &x) {
    bool sgn = 1; char c;
    while (!isdigit(c = rd())) if (c == '-') sgn = 0;
    x = c - '0';
    while (isdigit(c = rd())) x = x * 10 + (c - '0');
    if (!sgn) x = -x;
    return in;
}

inline fast_reader &operator>>(fast_reader &in, string &s) {
    char c;
    while (isspace(c = rd()));
    s = string(1, c);
    while (!isspace(c = rd())) s += c;
    return in;
}

constexpr int OUT_BUF_SZ = 1 << 17;
char out_buf[OUT_BUF_SZ];

size_t out_ptr = 0;
inline void flush_out() { fwrite(out_buf, 1, out_ptr, stdout); out_ptr = 0; }
inline void wt(char c) {
    static bool atexit_set = false;
    if (!atexit_set) assert(atexit(flush_out) == 0), atexit_set = true;

    if (out_ptr == OUT_BUF_SZ) flush_out();
    out_buf[out_ptr++] = c;
}

struct fast_writer {};

inline fast_writer &operator<<(fast_writer &out, char c) { wt(c); return out; }

template<typename T, enable_if_t<((is_integral_v<T> && !is_same_v<T, char>)
    || is_same_v<T, __int128_t> || is_same_v<T, __uint128_t>)>* = nullptr>
inline fast_writer &operator<<(fast_writer &out, T x) {
    static char num_buf[40];
    if (x < 0) wt('-'), x = -x;
    size_t i = 0;
    for (; x >= 10; x /= 10) num_buf[i++] = (x % 10) + '0';
    wt(x + '0');
    while (i) wt(num_buf[--i]);
    return out;
}

inline fast_writer &operator<<(fast_writer &out, const string &s) {
    for (const char &c : s) wt(c);
    return out;
}

} // namespace fast_io

fast_io::fast_reader fcin;
fast_io::fast_writer fcout;

} // namespace std

using std::fcin, std::fcout;

#define cin fcin
#define cout fcout
