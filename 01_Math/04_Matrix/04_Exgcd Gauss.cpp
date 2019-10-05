for(int i=2;i<=n;++i)
    for(int j=i+1;j<=n;++j)
        while(a[j][i]){
            int t=a[i][i]/a[j][i];
            for(int k=i;k<=n;++k)a[i][k]=(a[i][k]-1ll*a[j][k]*t%M+M)%M,swap(a[i][k],a[j][k]);
        }
