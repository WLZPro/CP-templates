# Tests

## Data Structures

### Fenwick Tree (fenwick_tree.hpp)
- [Point addition, range sum](https://judge.yosupo.jp/problem/point_add_range_sum) ($N, Q \leq 5 \times 10^5$): [57 ms](https://judge.yosupo.jp/submission/175608)

### Segment Tree (segment_tree.hpp)
- [Static range minimum](https://judge.yosupo.jp/problem/staticrmq) ($N, Q \leq 5 \times 10^5$): [98 ms](https://judge.yosupo.jp/submission/175610)
- [Static range sum](https://judge.yosupo.jp/problem/static_range_sum) ($N, Q \leq 5 \times 10^5$): [110 ms](https://judge.yosupo.jp/submission/175611)
- [Point addition, range sum](https://judge.yosupo.jp/problem/point_add_range_sum) ($N, Q \leq 5 \times 10^5$): [93 ms](https://judge.yosupo.jp/submission/175612)
- [Point modification, range linear function composition](https://judge.yosupo.jp/problem/point_set_range_composite) ($N, Q \leq 5 \times 10^5$): [149 ms](https://judge.yosupo.jp/submission/168743)

### crazySegmentTree (segment_tree_crazy.hpp)
- [Static range minimum](https://judge.yosupo.jp/problem/staticrmq) ($N, Q \leq 5 \times 10^5$): [75 ms](https://judge.yosupo.jp/submission/168740)

### Lazy Segment Tree (segment_tree_lazy.hpp)
- [Range $a_i \leftarrow c \cdot a_i + d$ updates, range sums](https://judge.yosupo.jp/problem/range_affine_range_sum) ($N, Q \leq 5 \times 10^5$): [635 ms](https://judge.yosupo.jp/submission/175771)

### Persistent Segment Tree (segment_tree_persistent.hpp)
- [Correctness](https://oj.uz/problem/view/COCI21_index): [882940](https://oj.uz/submission/882940)

### Sparse Table (sparse_table.hpp)
- [Static range minimum](https://judge.yosupo.jp/problem/staticrmq) ($N, Q \leq 5 \times 10^5$): [92 ms](https://judge.yosupo.jp/submission/175614)

### Implicit Treap (treap_implicit.hpp)
- [Point insertion and deletion, range $a_i \leftarrow c \cdot a_i + d$ updates, range reversals, range sum queries](https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum) ($N, Q \leq 5 \times 10^5$): [3742 ms](https://judge.yosupo.jp/submission/168888)

## Math

### Math utilities (math_utils.hpp)
- [Linear floor sum](https://judge.yosupo.jp/problem/sum_of_floor_of_linear) ($N, M \leq 10^9$): [52 ms](https://judge.yosupo.jp/submission/173167)

### Prime numbers and arithmetic functions (primes.hpp)
- Correctness of Möbius function: [231246540](https://codeforces.com/contest/1845/submission/231246540)
- Correctness of Euler phi function: [231246194](https://codeforces.com/contest/1797/submission/231246194)

### Matrices (matrix.hpp)
- [Matrix multiplication (mod 998244353)](https://judge.yosupo.jp/problem/matrix_product) ($N, M, K \leq 1024$): [1515 ms](https://judge.yosupo.jp/submission/170039)
- [Correctness of matrix exponentiation (mod 1000000007)](https://cses.fi/problemset/task/1096/): [7595524](https://cses.fi/paste/8ecd1ba48e13c19873e604/)

### GCD Convolution (gcd_convolution.hpp)
- [GCD Convolution (mod 998244353)](https://judge.yosupo.jp/problem/gcd_convolution) ($N \leq 10^6$): [123 ms](https://judge.yosupo.jp/submission/170565)

## Polynomials

### Fast Fourier Transform (fft.hpp)
- [Convolution/polynomial multiplication (mod 998244353)](https://judge.yosupo.jp/problem/convolution_mod) ($N, M \leq 524288$): [205 ms](https://judge.yosupo.jp/submission/168967)

### Power series (power_series.hpp)
- [Inverse of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/inv_of_formal_power_series) ($N \leq 5 \times 10^5$): [659 ms](https://judge.yosupo.jp/submission/168989)
- [Logarithm of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/log_of_formal_power_series) ($N \leq 5 \times 10^5$): [932 ms](https://judge.yosupo.jp/submission/168990)
- [Exponential of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/exp_of_formal_power_series) ($N \leq 5 \times 10^5$): [1278 ms](https://judge.yosupo.jp/submission/169042)

## Utilities

### Fast IO (fast_io.hpp)
- [Many A + B](https://judge.yosupo.jp/problem/many_aplusb) ($N \leq 10^6$): [107 ms](https://judge.yosupo.jp/submission/168745)