ll BSGS (ll a, ll b, ll p) {
    if (a %= p, b %= p, b == 1) return 0;
    ll t = 1; ll f, g, delta = 0, m = sqrt (p) + 1, i;
    for (g = gcd (a, p) ; g != 1; g = gcd (a , p) ){
        if (b % g) return -1;
        b /= g, p /= g, t = t * (a / g) % p, delta ++;
        if (b == t) return delta;
    }
    map <ll, ll> Hash;
    for (i = 0; i < m; i++, b = b * a % p) Hash [b] = i;
    for (i = 1, f = quickmod (a, m, p); i <= m + 1; i++)
    if (t = t * f % p, Hash.count (t) ) return i * m - Hash [t] + delta;
    return -1;
}