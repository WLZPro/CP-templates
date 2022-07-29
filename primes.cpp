bitset<(int) 1e5 + 1> is_prime;
vector<int> primes;

void gen_primes() {
  is_prime.set();
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= (int) 1e5; i++) {
    if (!is_prime[i]) continue;
    primes.push_back(i);
    for (int j = 2 * i; j <= (int) 1e5; j += i) is_prime[j] = false;
  }
}