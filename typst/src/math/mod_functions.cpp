const ll MOD = 1'000'000'007;

ll mult(ll a, ll b){
    return ((a%MOD)*(b%MOD))%MOD;
}

ll sum(ll a, ll b){
    return ((a%MOD)+(b%MOD))%MOD;
}

ll sub(ll a, ll b){
    return ((a%MOD) - (b%MOD) + MOD)%MOD;
}

ll pot(ll a, ll b){
    ll expo=1, prod=a;
    b = b % (MOD-1);
    a = a % MOD;

    while(b>=1){
        if(b%2 == 1) expo = mult(expo,prod);
        prod = mult(prod,prod);
        b = b/2;
    }
    
    return expo;
}

ll inv_mod(ll a){
    return pot(a, MOD-2);
}
