#ifndef MATH_POLYNOMIAL_HPP
#define MATH_POLYNOMIAL_HPP 1

#include <vector>

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

    // @note Hasn't been tested yet.
    inline poly &operator+=(const poly &rhs) {
        int n = static_cast<int>(this->size()), m = static_cast<int>(rhs.size());
        if (m > n) {
            this->reserve(m);
            for (int i = n; i < m; i++) this->push_back(0);
        }
        for (int i = 0; i < m; i++) this->operator[](i) += rhs[i];
        return *this;
    }

    // @note Hasn't been tested yet.
    inline friend poly operator+(poly lhs, const poly &rhs) { return lhs += rhs; }

    // @note Hasn't been tested yet.
    inline poly &operator-=(const poly &rhs) { 
        int n = static_cast<int>(this->size()), m = static_cast<int>(rhs.size());
        if (m > n) {
            this->reserve(m);
            for (int i = n; i < m; i++) this->push_back(0);
        }
        for (int i = 0; i < m; i++) this->operator[](i) -= rhs[i];
        return *this;
    }

    // @note Hasn't been tested yet.
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
};

template<typename T> using poly  = polynomial<T>;

// Defined in polynomial/fft.hpp
template<typename T> inline poly<T> &operator*=(poly<T>&, poly<T>);
template<typename T> inline poly<T>  operator* (poly<T> , const poly<T>&);

// Defined in polynomial/inv.hpp
template<typename T> inline poly<T> inv(const poly<T>&, int);
template<typename T> inline poly<T> inv(const poly<T>&);

// Defined in polynomial/log.hpp
template<typename T> inline poly<T> log(const poly<T>&, int);
template<typename T> inline poly<T> log(const poly<T>&);

#endif // MATH_POLYNOMIAL_HPP