// ---
// a mod数，r 余数，n长度，不要求mod数彼此互质\\
// 需要函数exgcd\\
// ExCRT返回答案
// ---
ll a [100005], r [100005]; int n;
ll ExCRT () {
    ll M = a [1], R = r [1], x, y, d;
    for (int i = 2; i <= n; i++) {
        d = exgcd (M, a [i], x, y);
        if ( (R - r [i]) % d != 0) return -1;
        x = (R - r [i]) / d * x % a [i];
        R -= x * M;
        M = M / d * a [i];
        R %= M;
    }
    return (R % M + M) % M;
}