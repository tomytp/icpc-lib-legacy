// Divide and Conquer DP
//
// Particiona o array em k subarrays
// minimizando o somatorio das queries
//
// O(k n log n), assumindo quer cost(l, r) eh O(1)

vector<v64> dp; // dp[n+1][2]

void solve(ll k, ll l, ll r, ll lk, ll rk) {
	if (l > r) return;
	ll m = (l+r)/2, p = -1;
	auto& ans = dp[m][k&1] = INF;
	for (ll i = max(m, lk); i <= rk; i++) {
		ll at = dp[i+1][~k&1] + cost(m, i);
		if (at < ans) ans = at, p = i;
	}
	solve(k, l, m-1, lk, p), solve(k, m+1, r, p, rk);
}

ll dnc(ll n, ll k) {
	dp[n][0] = dp[n][1] = 0;
	forn(i,0,n) dp[i][0] = INF;
	forn(i,1,k+1) solve(i, 0, n-i, 0, n-i);
	return dp[0][k&1];
}
