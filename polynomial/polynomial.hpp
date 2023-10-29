#ifndef POLYNOMIAL_POLYNOMIAL_HPP
#define POLYNOMIAL_POLYNOMIAL_HPP 1

#include <vector>
#include <string>

template<typename T>
class polynomial : public std::vector<T> {
    using poly = polynomial;

    public:
    using std::vector<T>::vector;

    constexpr friend int deg(const poly &p) { return static_cast<int>(p.size() - 1); }

    inline void expand_to(int n) {
        if (static_cast<int>(this->size()) >= n) return;
        this->reserve(n);
        while (static_cast<int>(this->size()) < n) this->push_back(0);
    }

    inline void truncate_to(int n) {
        while (static_cast<int>(this->size()) > n) this->pop_back();
        this->shrink_to_fit();
    }

    inline poly operator+() { return *this; }
    inline poly operator-() {
        poly ans(*this);
        for (int i = 0; i < deg(ans); i++) ans[i] = -ans[i];
        return ans;
    }

    inline poly &operator+=(const poly &rhs) {
        int n = static_cast<int>(this->size()), m = static_cast<int>(rhs.size());
        if (m > n) {
            this->reserve(m);
            for (int i = n; i < m; i++) this->push_back(0);
        }
        for (int i = 0; i < m; i++) this->operator[](i) += rhs[i];
        return *this;
    }

    inline friend poly operator+(poly lhs, const poly &rhs) { return lhs += rhs; }

    inline poly &operator-=(const poly &rhs) { 
        int n = static_cast<int>(this->size()), m = static_cast<int>(rhs.size());
        if (m > n) {
            this->reserve(m);
            for (int i = n; i < m; i++) this->push_back(0);
        }
        for (int i = 0; i < m; i++) this->operator[](i) -= rhs[i];
        return *this;
    }

    inline friend poly operator-(poly lhs, const poly &rhs) { return lhs -= rhs; }

    // @note Hasn't been tested yet.
    inline T operator()(const T &x) {
        T ans = 0;
        for (int i = 0; i < static_cast<int>(this->size()); i++) ans *= x, ans += this->operator[](i);
        return ans;
    }

    inline friend poly deriv(const poly &a) {
        poly ans(a.size() - 1);
        for (int i = 1; i < static_cast<int>(a.size()); i++) ans[i - 1] = a[i] * ((T) i);
        return ans;
    }

    inline friend poly integr(const poly &a) {
        poly ans(a.size() + 1); ans[0] = 0;
        for (int i = 0; i < static_cast<int>(a.size()); i++) ans[i + 1] = a[i] / ((T) (i + 1));
        return ans;
    }

    static constexpr poly constant(const T &a_0) { return {a_0}; }

    inline friend std::string to_string(const poly &a) {
        using std::to_string;
        std::string ans = "";
        bool first = true;
        for (int i = 0; i < static_cast<int>(a.size()); i++) {
            if (a[i] == 0) continue;
            if (a[i] < 0) {
                if (!first) ans += '-';
                if (a[i] != -1) ans += to_string(-a[i]);
                first = false;
            } else {
                if (!first) ans += '+';
                if (a[i] != 1) ans += to_string(+a[i]);
                first = false;
            }
            if (i > 0) ans += 'x';
            if (i > 1) ans += '^' + to_string(i);
        }
        return ans;
    }
};

template<typename T> using poly  = polynomial<T>;

// Defined in polynomial/fft.hpp
template<typename T> inline poly<T> &operator*=(poly<T>&, poly<T>);
template<typename T> inline poly<T>  operator* (poly<T> , const poly<T>&);

// Defined in polynomial/power_series.hpp
template<typename T> inline poly<T> inv(const poly<T>&, int);
template<typename T> inline poly<T> inv(const poly<T>&);

template<typename T> inline poly<T> log(const poly<T>&, int);
template<typename T> inline poly<T> log(const poly<T>&);

template<typename T> inline poly<T> exp(const poly<T>&, int);
template<typename T> inline poly<T> exp(const poly<T>&);

#endif // POLYNOMIAL_POLYNOMIAL_HPP