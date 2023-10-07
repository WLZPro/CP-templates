#ifndef MATH_MOD_SIMPLE_HPP
#define MATH_MOD_SIMPLE_HPP 1

const int MOD = (int) 1e9 + 7;

/** Assumes 1 <= a, b < MOD */
int add(int a, int b) {
    if (a + b >= MOD) return a + b - MOD;
    return a + b;
}

/** Assumes 1 <= a, b < MOD */
int sub(int a, int b) {
    return add(a, MOD - b);
}

/** Assumes 1 <= a, b < MOD */
int mul(int a, int b) {
    return (long long) a * b % MOD;
}

/** Assumes 1 <= b < MOD */
int modpow(int b, int p) {
    if (p == 0) return 1;
    int ans = modpow(mul(b, b), p / 2);
    if (p % 2 == 1) ans = mul(ans, b);
    return ans;
}

int extgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, g = extgcd(b, a % b, x1, y1);
    x = y1; y = sub(x1, mul(y1, (a / b) % MOD));
    return g;
}

/** Assumes gcd(x, MOD) = 1 */ 
int inv(int x) {
    int x1, y1;
    extgcd(x, MOD, x1, y1);
    return x1;
}

#endif // MATH_MOD_SIMPLE_HPP