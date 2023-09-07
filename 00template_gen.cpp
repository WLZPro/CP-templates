#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
//mt19937_64 rng_64;

void seed(const int &_seed) {
    rng.seed(_seed);
    //rng_64.seed(_seed);
}

int rand(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}

int rand(int a) {
    return rand(1, a);
}

double randreadl(double a, double b) {
    return uniform_real_distribution<double>(a, b)(rng);
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}
