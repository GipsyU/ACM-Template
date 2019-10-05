for (int i = 1; i <= N; ++i) U[i] = 1;
for (int i = 2; i <= N; ++i){
    if (v[i]) continue;
    for (int j = i; j <= N; j += i){
        v[j] = 1;
        if (j % (i * i) == 0) U[j] = 0;
        U[j] *= -1;
    }
}
u[1] = 1;
for (int i = 2; i <= N; ++i){
    if (! v[i]) u[i] = -1, p[++cnt] = i;
    for(int j = 1; j <= cnt && i * p[j] <= N; ++j){
        int k = i * p[j]; v[k] = 1;
        if(i % p[j]) u[k] = -u[i];
        else{
            u[k] = 0;
            break;
        }
    }
}
