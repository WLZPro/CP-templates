ll n;

// All O(sqrt(n)) floors, in descending order
for (ll v = 1; v <= n; v = n / (n / v) + 1) {
    ll x = n / v;   
}

// All O(sqrt(n)) ceils, in descending order
for (ll v = 1; v < n; v = (n - 1) / ((n - 1) / v) + 1) {
    ll x = (n - 1) / v + 1;
}
ll x = n;