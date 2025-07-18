vector<ll> g[MAX];
ll sz[MAX], rem[MAX];

void dfs(v64& path, ll i, ll l=-1, ll d=0) {
	path.push_back(d);
	for (ll j : g[i]) if (j != l and !rem[j]) dfs(path, j, i, d+1);
}

ll dfs_sz(ll i, ll l=-1) {
	sz[i] = 1;
	for (ll j : g[i]) if (j != l and !rem[j]) sz[i] += dfs_sz(j, i);
	return sz[i];
}

ll centroid(ll i, ll l, ll size) {
	for (ll j : g[i]) if (j != l and !rem[j] and sz[j] > size / 2)
		return centroid(j, i, size);
	return i;
}

ll decomp(ll i, ll k) {
	ll c = centroid(i, i, dfs_sz(i));
	rem[c] = 1;

    // gasta O(n) aqui - dfs sem ir pros caras removidos
	ll ans = 0;
	vector<ll> cnt(sz[i]);
	cnt[0] = 1;
	for (ll j : g[c]) if (!rem[j]) {
		vector<ll> path;
		dfs(path, j);
		for (ll d : path) if (0 <= k-d-1 and k-d-1 < sz[i])
			ans += cnt[k-d-1];
		for (ll d : path) cnt[d+1]++;
	}

	for (ll j : g[c]) if (!rem[j]) ans += decomp(j, k);
	rem[c] = 0;
	return ans;
}
