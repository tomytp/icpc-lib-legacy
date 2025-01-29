#define LC nd * 2 + 1
#define RC nd * 2 + 2

const T NEUTRAL = node_neutro;

struct SegTree {
  vector < T > tree;
  ll n;
  T op(const T & a,
    const T & b) {
    return a + b;
  }

  SegTree(const vector < T > & v): n(v.size()) {
    tree.resize(4 * n);
    _build(v, 0, 0, n - 1);
  }
  void update(ll idx,
    const T & val) {
    _update(idx, val, 0, 0, n - 1);
  }

  T query(ll l, ll r) {
    return _query(l, r, 0, 0, n - 1);
  }
  void _build(const vector < T > & v, ll nd, ll st, ll ed) {
    if (st == ed) {
      tree[nd] = v[st];
    } else {
      ll mid = (st + ed) / 2;
      _build(v, LC, st, mid);
      _build(v, RC, mid + 1, ed);
      tree[nd] = op(tree[LC], tree[RC]);
    }
  }
  void _update(ll idx,
    const T & val, ll nd, ll st, ll ed) {
    if (st == ed) tree[nd] = val;
    else {
      ll mid = (st + ed) / 2;
      if (idx <= mid) _update(idx, val, LC, st, mid);
      else _update(idx, val, RC, mid + 1, ed);
      tree[nd] = op(tree[LC], tree[RC]);
    }
  }
  T _query(ll l, ll r, ll nd, ll st, ll ed) {
    if (r < st || ed < l) return NEUTRAL;
    if (l <= st && ed <= r) return tree[nd];
    ll mid = (st + ed) / 2;
    T left = _query(l, r, LC, st, mid);
    T right = _query(l, r, RC, mid + 1, ed);
    return op(left, right);
  }
};