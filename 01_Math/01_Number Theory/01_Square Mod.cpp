// ---
// 二次剩余
// ---
struct T{
    ll p, d;
};
ll w;
//二次域乘法
T multi_er(T a, T b, ll m){
    T ans;
    ans.p = (a.p * b.p % m + a.d * b.d % m * w % m) % m;
    ans.d = (a.p * b.d % m + a.d * b.p % m) % m;
    return ans;
}
//二次域上快速幂
T power(T a, ll b, ll m){
    T ans;
    ans.p = 1;
    ans.d = 0;
    while(b){
        if(b & 1){
            ans = multi_er(ans, a, m);
            b--;
        }
        b >>= 1;
        a = multi_er(a, a, m);
    }
    return ans;
}
//求勒让德符号
ll Legendre(ll a, ll p){
    return quick_mod(a, (p-1)>>1, p);
}
ll mod(ll a, ll m){
    a %= m;
    if(a < 0) a += m;
    return a;
}
ll Solve(ll n,ll p){
    if(p == 2) return 1;
    if (Legendre(n, p) + 1 == p)
        return -1;
    ll a = -1, t;
    while(true){
        a = rand() % p;
        t = a * a - n;
        w = mod(t, p);
        if(Legendre(w, p) + 1 == p) break;
    }
    T tmp;
    tmp.p = a;
    tmp.d = 1;
    T ans = power(tmp, (p + 1)>>1, p);
    return ans.p;
}
int main()
    int n, p;
    scanf("%d %d",&n,&p);
    n %= p;
    int a = Solve(n, p);
    if(a == -1) puts("No root");
    int b = p - a;
    if(a > b) swap(a, b);
    if(a == b) printf("%d\n",a);
    else printf("%d %d\n",a,b);
}