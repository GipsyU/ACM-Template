ll f(ll a,ll b,ll c,ll n){
    if (n==0) return 0;
    ll ans=(b/c)*n*(n-1)/2+(a/c)*n;
    ans=ans+f((b*n+a)%c,c,b%c,((b%c)*n+(a%c))/c);
    return ans;
}
ll F(ll x,ll y,ll z){
    ll ans=0;
    for (ll u=0;u<40;u++)
        ans=ans|((f(x,z,(1ll<<u),(y-x)/z+1)&1)<<u); 
    return ans;
}