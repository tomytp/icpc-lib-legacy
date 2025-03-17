v64 topo_sort(const vector<v64>& g) {
	v64 indeg(g.size()), q;
	for (auto& li : g) for (int x : li) indeg[x]++;
	forn(i, 0, g.size()) if (indeg[i] == 0) q.push_back(i);
	forn(j, 0, q.size()) for(int x : g[q[j]]) if(--indeg[x] == 0) q.push_back(x);
	return q;
}