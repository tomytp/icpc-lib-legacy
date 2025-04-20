template<typename T, T (*comb)(T, T), T neutral>
struct node {
    ll lm, rm;
    unique_ptr<node> l_child, r_child;
    T val = 0;

    node(ll lm_, ll rm_, vector<T>& v) : lm(lm_), rm(rm_), l_child(nullptr), r_child(nullptr) {
        if (lm == rm) {
            val = v[lm];
        } else {
            ll mid = (lm + rm) / 2;
            l_child = make_unique<node>(lm, mid, v);
            r_child = make_unique<node>(mid+1, rm, v);
            calc();
        }
    }

    void calc() {
        if (lm == rm) return;
        val = comb(l_child->val, r_child->val);
    }


    void point_update(ll idx, ll n_val) {
        if (lm == rm) {
            val = n_val;
            return;
        }

        if (idx <= l_child->rm) l_child->point_update(idx, n_val);
        else r_child->point_update(idx, n_val);
        calc();
    }

    ll rq(ll l, ll r) {
        if (l > rm || r < lm) return neutral;
        if (l <= lm && r >= rm) return val;
        return comb(l_child->rq(l, r), r_child->rq(l, r));
    }
};