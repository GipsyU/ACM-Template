const int N=;
struct SparseTable{
    int f[N][20];
    void build(int n){
        for(int i=1;i<=n;++i)f[i][0]=A[i];
        for(int j=1;(1<<j)<=n;++j)
            for(int i=1;i+(1<<j)-1<=n;++i)
                f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    }
    int ask(int l,int r){
        int k=31-__bulitin_clz(r-l+1);
        return max(f[l][k],f[r-(1<<k)+1][k]);
    }
}ST;
