$\renewcommand{\O}{\mathcal{O}}$

## Sum estimations

$\frac{n}{1} + \frac{n}{2} + \dots + \frac{n}{n} = \O(n \log n)$

$1^r + 2^r + \dots + n^r = \O(n^{r + 1})$ for any real $r \ne -1$ (Examples: [CF 1801F](https://codeforces.com/contest/1801/problem/F) ($r = -\frac{1}{2}$))

## Floor and ceiling functions

There are $\O(\sqrt n)$ different numbers in $\left\lfloor \frac{n}{1} \right\rfloor$, $\left\lfloor \frac{n}{2} \right\rfloor$, ..., $\left\lfloor \frac{n}{n} \right\rfloor$. They can be enumerated efficiently using
```cpp
for (int k = 1; k <= n; k = n / (n / k) + 1) {
    // Do something with n / k
}
```
This also works for ceilings, by noting that $\left\lceil \frac{n}{k} \right\rceil = \left\lfloor \frac{n - k + 1}{k} \right\rfloor = \left\lfloor \frac{n - 1}{k} \right\rfloor + 1$. $k = n$ will have to be checked separately.
(Examples: [CF 1801F](https://codeforces.com/contest/1801/problem/F))
