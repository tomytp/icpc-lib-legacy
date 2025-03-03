//1-indexed
struct BIT {
    v64 ft;
    BIT(ll n) {
        ft.assign(n+1, 0);
    }

    ll rsq(ll i) {
        ll sum = neutral;
        for (;i; i-=(i&-i)) sum = comp(sum, ft[i]);
        return sum;
    }

    ll rsq(ll i, ll j) {
        return rsq(j) - rsq(i-1);
    }

    void add(ll i, ll v) {
        for(;i<(ll)ft.size(); i+= (i&-i)) ft[i] = comp(ft[i], v);
    }
};
