#ifndef UTIL_FAST_IO_HPP
#define UTIL_FAST_IO_HPP 1

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstdlib>

namespace fast_input {

    constexpr int BUF_SZ = 1 << 18;
    char buf[BUF_SZ];
    int pos = 0, len = 0;

    #define rd (pos == len ? (pos = 0, (!(len = (int) fread(buf, 1, BUF_SZ, stdin)) ? EOF : buf[pos++])) : buf[pos++])

    template<typename T>
    void read(T &x) {
        short sgn = 1; char c;
        while (!std::isdigit(c = rd)) if (c == '-') sgn = -sgn;
        x = c - '0';
        while (std::isdigit(c = rd)) { x = x * 10 + (c - '0'); }
    }

    #undef rd

    struct fast_reader { void tie(int *x) {} } fcin;
} // namespace fast_input

template<typename T>
fast_input::fast_reader &operator>>(fast_input::fast_reader &in, T &x) { fast_input::read(x); return in; }

namespace fast_output {

    constexpr int BUF_SZ = 1 << 18;
    char buf[BUF_SZ];
    int pos;

    void flush() { fwrite(buf, 1, pos, stdout); pos = 0; }
    void sync_with_stdio(bool b) { assert(std::atexit(flush) == 0); }

    #define wt(c) ((pos == BUF_SZ ? flush() : (void) 0), buf[pos++] = (c))

    template<typename T>
    void write(const T &y) {
        T x = y;
        static char num_buf[100];
        if (x < 0) wt('-'), x = -x;
        int len = 0;
        for (; x >= 10; x /= 10) num_buf[len++] = (x % 10) + '0';
        wt(x + '0');
        while (len) wt(num_buf[--len]);
    }

    template<>
    void write(const char &c) { wt(c); }

    #undef wt

    struct fast_writer {} fcout;
} // namespace fast_output

template<typename T>
fast_output::fast_writer &operator<<(fast_output::fast_writer &out, const T &x) { fast_output::write(x); return out; }

#define cin fast_input::fcin
#define ios fast_output
#define cout fast_output::fcout

#endif // UTIL_FAST_IO_HPP
