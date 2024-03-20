# Tests

## Data Structures

### Hash Map (hash_map.hpp)
- [Large index accesses](https://judge.yosupo.jp/problem/associative_array) ($Q \leq 10^6$): `safe_unordered_map`: [528 ms](https://judge.yosupo.jp/submission/178294), `safe_gp_hash_table`: [243 ms](https://judge.yosupo.jp/submission/178295)

### Fenwick Tree (fenwick_tree.hpp)
- [Point addition, range sum](https://judge.yosupo.jp/problem/point_add_range_sum) ($N, Q \leq 5 \times 10^5$): [57 ms](https://judge.yosupo.jp/submission/183061)

### Segment Tree (segment_tree.hpp)
- [Static range minimum](https://judge.yosupo.jp/problem/staticrmq) ($N, Q \leq 5 \times 10^5$): [98 ms](https://judge.yosupo.jp/submission/175610)
- [Static range sum](https://judge.yosupo.jp/problem/static_range_sum) ($N, Q \leq 5 \times 10^5$): [110 ms](https://judge.yosupo.jp/submission/175611)
- [Point addition, range sum](https://judge.yosupo.jp/problem/point_add_range_sum) ($N, Q \leq 5 \times 10^5$): [93 ms](https://judge.yosupo.jp/submission/175612)
- [Point modification, range linear function composition](https://judge.yosupo.jp/problem/point_set_range_composite) ($N, Q \leq 5 \times 10^5$): [149 ms](https://judge.yosupo.jp/submission/168743)

### AVX Segment Tree (segment_tree_avx.hpp)
- [Static range minimum](https://judge.yosupo.jp/problem/staticrmq) ($N, Q \leq 5 \times 10^5$): [103 ms](https://judge.yosupo.jp/submission/188379)

### Lazy Segment Tree (segment_tree_lazy.hpp)
- [Range $a_i \leftarrow c \cdot a_i + d$ updates, range sums](https://judge.yosupo.jp/problem/range_affine_range_sum) ($N, Q \leq 5 \times 10^5$): [588 ms](https://judge.yosupo.jp/submission/179964)

### Persistent Segment Tree (segment_tree_persistent.hpp)
- [Correctness](https://oj.uz/problem/view/COCI21_index): [882940](https://oj.uz/submission/882940)

### Sparse Table (sparse_table.hpp)
- [Static range minimum](https://judge.yosupo.jp/problem/staticrmq) ($N, Q \leq 5 \times 10^5$): [92 ms](https://judge.yosupo.jp/submission/175614)

### Li Chao Tree (li_chao_tree.hpp)
#### Static Li Chao Tree
- [Linear function insertion, point minimum queries](https://judge.yosupo.jp/problem/line_add_get_min) ($N, Q \leq 2 \times 10^5$): [159 ms](https://judge.yosupo.jp/submission/180515)
- [Linear function insertion on an interval, point minimum queries](https://judge.yosupo.jp/problem/segment_add_get_min) ($N, Q \leq 2 \times 10^5$): [469 ms](https://judge.yosupo.jp/submission/180514)

### Implicit Treap (treap_implicit.hpp)
- [Point insertion and deletion, range $a_i \leftarrow c \cdot a_i + d$ updates, range reversals, range sum queries](https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum) ($N, Q \leq 5 \times 10^5$): [2015 ms](https://judge.yosupo.jp/submission/179337)
- [Range reversals, range sum](https://judge.yosupo.jp/problem/range_reverse_range_sum) ($N, Q \leq 2 \times 10^5$): [450 ms](https://judge.yosupo.jp/submission/179324)
- [Static range reversals](https://codeforces.com/contest/1878/problem/D) ($N, Q \leq 2 \times 10^5$): [436 ms](https://codeforces.com/contest/1878/submission/236327907)

### Wavelet Tree (wavelet_tree.hpp)
- [Range k-th smallest](https://judge.yosupo.jp/problem/range_kth_smallest) ($N, Q \leq 2 \times 10^5$): [442 ms](https://judge.yosupo.jp/submission/188997)

### Union Find (union_find.hpp)
- [Union find](https://judge.yosupo.jp/problem/unionfind) ($N, Q \leq 2 \times 10^5$): [10 ms](https://judge.yosupo.jp/submission/175863)

## Dynamic Programming

### (min, +) convolution
- [(min, +) convolution (convex-convex)](https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex) ($N, M \leq 2^19$): [48 ms](https://judge.yosupo.jp/submission/178370)

## Graphs

### Heavy-light Decomposition (hld.hpp)
- [Vertex addition, path sum](https://judge.yosupo.jp/problem/vertex_add_path_sum) ($N, Q \leq 5 \times 10^5$): [1042 ms](https://judge.yosupo.jp/submission/179969)
- [Vertex modification, path linear function composition](https://judge.yosupo.jp/problem/vertex_set_path_composite) ($N, Q \leq 2 \times 10^5$): [367 ms](https://judge.yosupo.jp/submission/179970)
- [Vertex addition, subtree sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum) ($N, Q \leq 5 \times 10^5$): [442 ms](https://judge.yosupo.jp/submission/179971)

### Lowest Common Ancestor (jump pointers) (lca_jump_pointers.hpp)
- [Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca) ($N, Q \leq 5 \times 10^5$): [408 ms](https://judge.yosupo.jp/submission/178320)

### Lowest Common Ancestor (Farach-Colton and Bender) (lca_farach_colton_bender.hpp)
- [Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca) ($N, Q \leq 5 \times 10^5$): [276 ms](https://judge.yosupo.jp/submission/178321)

### Strongly Connected Components (scc.hpp)
- [Strongly Connected Components](https://judge.yosupo.jp/problem/scc) ($N, M \leq 5 \times 10^5$): [269 ms](https://judge.yosupo.jp/submission/178430)

### 2-SAT (two_sat.hpp)
- [2-SAT](https://judge.yosupo.jp/problem/two_sat) ($N, M \leq 5 \times 10^5$): [460 ms](https://judge.yosupo.jp/submission/178524)

### $k$ Shortest Walks (k_shortest_walks.cpp)
- [$k$ Shortest Walks](https://judge.yosupo.jp/problem/k_shortest_walk) ($N, M, K \leq 3 \times 10^5$): [181 ms](https://judge.yosupo.jp/submission/192151)

### Maximum Flow - Dinic's Algorithm (flow/dinic.cpp)
- [Maximum Flow](https://cses.fi/problemset/task/1694/): ($N \leq 500, M \leq 1000$): [8561749](https://cses.fi/paste/956a8ab820c14c0382a0e2/)
- [Maximum Flow, undirected](https://www.spoj.com/problems/FASTFLOW/) ($N \leq 5000, M \leq 3 \times 10^4$): [32684599](https://www.spoj.com/status/ns=32684599)

## Math

### Linear floor sum (linear_floor_sum.hpp)
- [Linear floor sum](https://judge.yosupo.jp/problem/sum_of_floor_of_linear) ($N, M \leq 10^9$): [52 ms](https://judge.yosupo.jp/submission/173167)

### Prime numbers and arithmetic functions (primes.hpp)
- Correctness of Möbius function: [231246540](https://codeforces.com/contest/1845/submission/231246540)
- Correctness of Euler phi function: [231246194](https://codeforces.com/contest/1797/submission/231246194)

### Miller-Rabin Primality Test (miller_rabin.hpp)
- [Deterministic primality test](https://judge.yosupo.jp/problem/primality_test) ($T \leq 10^5$, $N \leq 10^{18}$): [147 ms](https://judge.yosupo.jp/submission/181021)

### Integer factorization (factorization.cpp)
- [Integer factorization](https://judge.yosupo.jp/problem/factorize) ($T \leq 100$, $N \leq 10^{18}$): [23 ms](https://judge.yosupo.jp/submission/181023)

### Primitive Root (primitive_root.hpp)
- [Primitive root modulo a prime](https://judge.yosupo.jp/problem/primitive_root) ($T \leq 100, p \leq 10^{18}$): [12 ms](https://judge.yosupo.jp/submission/181478)

### Matrices (matrix.hpp)
- [Matrix multiplication (mod 998244353)](https://judge.yosupo.jp/problem/matrix_product) ($N, M, K \leq 1024$): [1515 ms](https://judge.yosupo.jp/submission/170039)
- [Correctness of matrix exponentiation (mod 1000000007)](https://cses.fi/problemset/task/1096/): [7595524](https://cses.fi/paste/8ecd1ba48e13c19873e604/)

### GCD Convolution (gcd_convolution.hpp)
- [GCD Convolution (mod 998244353)](https://judge.yosupo.jp/problem/gcd_convolution) ($N \leq 10^6$): [123 ms](https://judge.yosupo.jp/submission/170565)

### 128-bit Integers (int128.hpp)
- [Many A + B (128 bit)](https://judge.yosupo.jp/problem/many_aplusb_128bit) ($N \leq 5 \times 10^5$): [568 ms](https://judge.yosupo.jp/submission/178276)

### Fast Fourier Transform (polynomial/fft.hpp)
- [Convolution/polynomial multiplication (mod 998244353)](https://judge.yosupo.jp/problem/convolution_mod) ($N, M \leq 524288$): [205 ms](https://judge.yosupo.jp/submission/168967)

### Number Theoretic Transform using Montgomery Multiplication (polynomial/ntt_montgomery.hpp)
- [Convolution/polynomial multiplication (mod 998244353)](https://judge.yosupo.jp/problem/convolution_mod) ($N, M \leq 524288$): [79 ms](https://judge.yosupo.jp/submission/197143)

### Power Series Inverse (polynomial/power_series_inv.hpp)
- [Inverse of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/inv_of_formal_power_series) ($N \leq 5 \times 10^5$): [107 ms](https://judge.yosupo.jp/submission/197344)

### Power Series Logarithm (polynomial/power_series_log.hpp)
- [Logarithm of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/log_of_formal_power_series) ($N \leq 5 \times 10^5$): [199 ms](https://judge.yosupo.jp/submission/197425)

### Euclidean Division (div_mod) of Polynomials (polynomial/euclidean_division.hpp)
- [Euclidean Division of Polynomials](https://judge.yosupo.jp/problem/division_of_polynomials) ($N, M \leq 5 \times 10^5$): [329 ms](https://judge.yosupo.jp/submission/197988)

### Power series (polynomial/power_series.hpp)
- [Inverse of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/inv_of_formal_power_series) ($N \leq 5 \times 10^5$): [641 ms](https://judge.yosupo.jp/submission/176511)
- [Logarithm of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/log_of_formal_power_series) ($N \leq 5 \times 10^5$): [958 ms](https://judge.yosupo.jp/submission/176510)
- [Exponential of Formal Power Series (mod 998244353)](https://judge.yosupo.jp/problem/exp_of_formal_power_series) ($N \leq 5 \times 10^5$): [1245 ms](https://judge.yosupo.jp/submission/176508)

## Strings

### Z-function (z_function.hpp)
- [Z-function](https://judge.yosupo.jp/problem/zalgorithm) ($N \leq 5 \times 10^5$) : [13 ms](https://judge.yosupo.jp/submission/179218)

## Utilities

### Fast IO (fast_io.hpp)
- [Many A + B](https://judge.yosupo.jp/problem/many_aplusb) ($N \leq 10^6$): [107 ms](https://judge.yosupo.jp/submission/178270)
- [Many A + B (128 bit)](https://judge.yosupo.jp/problem/many_aplusb_128bit) ($N \leq 5 \times 10^5$) ($$): [293 ms](https://judge.yosupo.jp/submission/178273)