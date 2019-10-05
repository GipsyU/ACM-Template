// ---
// 线性处理逆元
// ---
inv [0] = 0;
inv [1] = 1;
for (int i = 2; i < n; i ++) {
    inv [i] = (M-1ll * M / i * inv [M % i] % M) % M;
}