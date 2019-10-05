const double eps=1e-8;
double a[N][N];
void gauss(int n){
	for(int i=1;i<=n;++i){
		int mx=i;
        for(int j=i+1;j<=n;j++){
            if(fabs(a[j][i])>fabs(a[mx][i]))mx=j;
        }
        if(mx!=i)for(int j=1;j<=n;j++)swap(a[i][j],a[mx][j]);
		for(int j=1;j<=n;++j){
			if(i==j)continue;
			double rate=a[j][i]/a[i][i];
			for(int k=i;k<=n;++k)a[j][k]-=a[i][k]*rate;
		}
	}
}
