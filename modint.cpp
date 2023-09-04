template<typename T, T MOD> 
class modint {
  private:
    T val;

  public:
    modint<T, MOD>() {
      val = 0;
    }

    modint<T, MOD>(const T& x) {
      val = x % MOD;
    }

    modint<T, MOD>& operator=(const T& x) {
      val = x % MOD;
      return *this;
    }

    modint<T, MOD>& operator=(const modint<T, MOD>& a) {
      val = a.val;
      return *this;
    }

    operator T() {
      return val;
    }

    modint<T, MOD>& operator++() {
      val++;
      if (val == MOD) {
        val = 0;
      }
      return *this;
    }

    modint<T, MOD> operator++(int) {
      modint<T, MOD> tmp = *this;
      val++;
      if (val == MOD) {
        val = 0;
      }
      return *this;
    }

    modint<T, MOD>& operator--() {
      val--;
      if (val < 0) {
        val = MOD - 1;
      }
      return *this;
    }

    modint<T, MOD> operator--(int) {
      modint<T, MOD> tmp = *this;
      val--;
      if (val < 0) {
        val = MOD - 1;
      }
      return *this;
    }
};

template<typename T, T MOD>
modint<T, MOD> operator+(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return {(a.val + b.val) % MOD};
}

template<typename T, T MOD>
modint<T, MOD> operator-(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return {((a.val - b.val) % MOD + MOD) % MOD};
}

/** a.val * b.val must not overflow */
template<typename T, T MOD>
modint<T, MOD> operator*(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return {(a.val * b.val) % MOD};
}

template<typename T, T MOD>
modint<T, MOD> pow(const modint<T, MOD>& b, long long p) {
  if (p == 0) {
    return {1};
  }
  modint<T, MOD> ans = pow(b * b, p / 2);
  if (p % 2 == 1) {
    ans *= b;
  }
  return ans;
}


/** assumes b and MOD are coprime */
template<typename T, T MOD>
modint<T, MOD> operator/(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return {a * pow(b, MOD - 2) % MOD};
}

template<typename T, T MOD>
modint<T, MOD>& operator+=(modint<T, MOD>& a, const modint<T, MOD>& b) {
  a = a + b;
  return a;
}

template<typename T, T MOD>
modint<T, MOD>& operator-=(modint<T, MOD>& a, const modint<T, MOD>& b) {
  a = a - b;
  return a;
}

template<typename T, T MOD>
modint<T, MOD>& operator*=(modint<T, MOD>& a, const modint<T, MOD>& b) {
  a = a * b;
  return a;
}

/** assumes b and MOD are coprime */
template<typename T, T MOD>
modint<T, MOD>& operator/=(modint<T, MOD>& a, const modint<T, MOD>& b) {
  a = a / b;
  return a;
}

template<typename T, T MOD>
inline bool operator==(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return (a.val == b.val);
}

template<typename T, T MOD>
inline bool operator!=(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return !(a == b);
}

template<typename T, T MOD>
inline bool operator<(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return (a.val < b.val);
}

template<typename T, T MOD>
inline bool operator>(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return (b < a);
}

template<typename T, T MOD>
inline bool operator<=(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return !(a > b);
}

template<typename T, T MOD>
inline bool operator>=(const modint<T, MOD>& a, const modint<T, MOD>& b) {
  return !(a < b);
}
