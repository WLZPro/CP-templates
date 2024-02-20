// https://oi-wiki.org/math/number-theory/min-25/
// https://codeforces.com/blog/entry/92703

const int SQ = 2e6+5; // 2*sqrt(MAXN)
vi spf, pr; // spf stores smallest prime factor,
			// pr lists primes <= sqrt(n) with pr[0] = 1
using i128 = __int128_t;
i128 fp[SQ], f[SQ], g[2][SQ];
// Example: sum of Euler phi function
i128 min25(ll n) {
	vector<ll> flr; flr.reserve(2*sqrtl(n));
	for (ll k=1;k<=n;k=n/(n/k)+1) flr.push_back(n/k);
	reverse(all(flr));
	int k = SZ(flr);
#define IDX(m) ((m)<=k/2 ? (m)-1 : k-n/(m))
	rep(i, 0, k) {
		ll m = flr[i];
		// Prefix sum of f(p) from 2 to m, separately for every term of f(p)
		g[0][i]=m-1; g[1][i]=i128(m+2)*(m-1)/2;
	}
	rep(j, 1, SZ(pr)) repr(i, k, 0) {
		ll m = flr[i];
		if (ll(pr[j])*pr[j]>m) break;
		// f(p) = p-1, so 1 and p
		g[0][i]-=  1  *(g[0][IDX(m/pr[j])]-g[0][pr[j-1]-1]);
		g[1][i]-=pr[j]*(g[1][IDX(m/pr[j])]-g[1][pr[j-1]-1]);
	}
	rep(i, 0, k) f[i] = fp[i] = g[1][i]-g[0][i]; // Terms of f(p)
	repr(j, SZ(pr), 1) repr(i, k, 0) {
		ll m=flr[i],p=pr[j];
		if (p*p>m) break;
		for (ll c=1,pc1=1,pc=p; pc*p<=m; pc1*=p,pc*=p,c++) {
			f[i] += (pc*(p-1)); // f(p^(c+1))
			f[i] += (pc1*(p-1)) * (f[IDX(m/pc)]-fp[p-1]);
					// f(p^c)
		}
	}
	return f[k - 1] + 1;
}