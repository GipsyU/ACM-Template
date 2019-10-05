inline ll qmul(ll x, ll y, ll mod){
    ll t = (x * y - (ll)((long double)x / mod * y + 1.0e-8) * mod);
    return t < 0 ? t + mod : t;
}