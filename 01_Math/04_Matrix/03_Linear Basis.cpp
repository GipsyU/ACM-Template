struct Linear_Basis {
    ll d [63], p [63], tot;
    void init () {
        tot = 0;
        memset (d, 0, sizeof (d) );memset (p, 0, sizeof (p) );
    }
    bool ins (ll x) {
        for (int i = 62; i >= 0; i--)
            if (x & (1ll << i) ) {
                if (! d[i]) {d [i] = x; break;}
                x ^= d [i];
            }
        return x>0;
    }
} LB;
