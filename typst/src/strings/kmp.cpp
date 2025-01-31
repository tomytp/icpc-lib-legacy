v64 pi(const string& s) {
    ll n = s.size();
	v64 p(n);
	forn(i, 1, n) {
		ll g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

v64 match(const string& s, const string& pat) {
	v64 p = pi(pat + '\0' + s), res;
	ll pz = p.size(), sz = s.size(), patz = pat.size();
    forn(i, pz - sz, pz)
		if (p[i] == patz) res.push_back(i - 2 * patz);
	return res;
}