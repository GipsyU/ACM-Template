// ---
// MR(次数(3),需要判断的质数) 是质数返回1\\
// find(需要分解的数,次数(100)) 返回在a数组中\\
// 需要大数mul,gcd,大数快速幂quickmod
// ---
vector <ll> a;
bool TD(ll a,ll n){
    ll m=n-1,x,y; int num=0;
    while (!(m&1)) m>>=1,num++;
    x=quickmod(a,m,n);
    for (int i=1;i<=num;x=y,i++){
        y=quickmod(x,2,n);
        if ((y==1)&&(x!=1)&&(x!=n-1))
            return true;
    }
    return y!=1;
}
bool MR(int t,ll x){
    if (x==1) return false;
    if (x==2) return true;
    if (!(x&1)) return false;
    while (t--) 
        if (TD(rand()%(x-1)+1,x))
            return false;
    return true;
}
ll PR(ll n,int t){
    ll i=1,k=2,x=rand()%n,y=x,d;
    while (1){
        i++,x=(mul(x,x,n)+t)%n,d=gcd(y-x,n);
        if (d>1&&d<n) return d;
        if (y==x) return n;
        if (i==k) y=x,k<<=1;
    }
}
void find(ll x,int k){
    if (x==1) return;
    if (MR(3,x)) return (void)a.push_back(x);
    ll t=x;
    while (t==x) t=PR(x,k--);
    find(t,k),find(x/t,k);
}