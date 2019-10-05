// ---
// 计算欧拉函数和莫比乌斯函数的前缀和\\
// 处理的数据范围1e12
// ---
const int N = 4e6;
int prime [N + 10], tot;
int v [N + 10];
ll phi [N + 10];
ll miu [N + 10];
map <ll, ll> _phi, _miu;
ll calcmiu (ll n) {
    if (n < N) return miu [n];
    if (_miu.count (n) ) return _miu [n];
    ll x = 2, ans = 1;
    while (x <= n) {
        ll y = n / (n / x);
        ans -= calcmiu (n / x) * ( y - x + 1);
        x = y + 1;
    }
    return _miu [n] = ans;
}
ll calcphi (ll n) {
    if (n < N) return phi [n];
    if (_phi.count (n) ) return _phi [n];
    ll x = 2, ans = n * (n + 1) / 2;
    while (x <= n){
        ll y = n / (n / x);
        ans -= calcphi (n / x) * ( y - x + 1);
        x = y + 1;
    }
    return _phi [n] = ans;
}

int main(){
    // 计算出phi和miu
    for (int i = 2; i <= N; ++i) {
        phi [ i ] += phi [ i - 1 ];
        miu [ i ] += miu [ i - 1 ];
    }
    ll x;
    scanf ("%lld", &x);
    cout << calcphi (x) << " " << calcmiu (x) << endl;
}