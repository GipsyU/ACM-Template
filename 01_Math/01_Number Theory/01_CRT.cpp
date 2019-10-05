// ---
// r为数组长度\\
// m是mod数，需要相互互质\\
// a是mod后的余数\\
// M 最小共倍数\\
// ans 答案
// ---
void ChinaRT (int r, int *m, int *a, int &M, int &ans) {
    M = 1, ans = 0;
    int x, y; 
    for (int i = 1; i <= r; ++i) M *= m[i];
    for (int i = 1; i <= r; ++i) {
        exgcd (M / m[i], m[i], x, y);
        ans = (ans + M / m[i] * x * a[i]) % M;
    }
    if (ans < 0) ans += M;
}