const ll INF = 1'000'000'000'000;
vector<vp64> adj; // (v, w)

// d = distance | p = path
void dijkstra(ll s, v64 &d, v64& p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    priority_queue<p64, vp64, greater<p64>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ll u = pq.top().second;
        ll d_u = pq.top().first;
        pq.pop();

        if (d_u != d[u]) continue;

        for (auto edge : adj[u]) {
            ll v = edge.first;
            ll w_v = edge.second;

            if (d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                p[v] = u;
                pq.push({d[v], v});
            }
        }
    }
}
