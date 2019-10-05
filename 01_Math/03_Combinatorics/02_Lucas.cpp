// ---
// Caculate C(n,m)mod p
// p must be a prime
// ---
ll C(ll n,ll m){
    return n<m||m<0?0:JC[n]*INV[m]%M*INV[n-m]%M;
}
ll Lucas(ll n,ll m){
    return m?C(n%M,m%M)*Lucas(n/M,m/M)%M:1;
}
