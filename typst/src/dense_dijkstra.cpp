#define INF 1'000'000'000'000
vector<vp64> adj; // (v, w)

// d = distance | p = path
void dijkstra(int s, v64& d, v64& p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> visited(n, false);

    d[s] = 0;
    forn(i, 0, n) {
        ll u = -1;
        forn(j, 0, n) {
            if (!visited[j] && (u == -1 || d[j] < d[u])) u = j;
        }

        if (d[u] == INF) break;

        visited[u] = true;
        for (auto edge : adj[u]) {
            ll v = edge.first;
            ll w_v = edge.second;

            if (d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                p[v] = u;
            }
        }
    }
}
