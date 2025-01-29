ll parent[MAXN]; //Inicializar parent[i] = i
ll sz[MAXN];

ll find(ll x){
    ll pai = x;
    ll filho = x;
    ll aux;
    while( pai != parent[pai] ) pai = parent[pai];
    while( filho != parent[filho] ) {
        aux = parent[filho];
        parent[filho] = pai;
        filho = aux;
    }
    return pai;
}
  
void uni(ll x, ll y){
    ll rx = find(x);
    ll ry = find(y);
    if(rx == ry) return;
    if( sz[rx] < sz[ry]) swap(rx,ry);
    parent[ry] = rx;
    sz[rx] += sz[ry]; 
    return;
}