const int N=3e5+10;
struct HisTree{
    int l,r,sum;
}T[N*20];
int tot,cnt,ver[N],head[N],Next[N],d[N],fa[N],n,m,R[N],A[N],f[N][20],t;
vector<int> V;
int getid(int x){
    return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
}
void add(int x,int y){
    ver[++tot]=y;Next[tot]=head[x];head[x]=tot;
}
void build(int l,int r,int &x,int y,int pos){
    T[++cnt]=T[y],x=cnt,T[x].sum++;
    if(l==r)return;
    int mid=(l+r)/2;
    if(pos<=mid)build(l,mid,T[x].l,T[y].l,pos);
    else build(mid+1,r,T[x].r,T[y].r,pos);
}
void dfs(int x,int y){
    fa[x]=y;
    for(int i=head[x];i;i=Next[i]){
        if(ver[i]==y)continue;
        build(1,n,R[ver[i]],R[x],getid(A[ver[i]]));
        dfs(ver[i],x);
    }
}
void bfs(){
    queue<int> Q;
    Q.push(1);d[1]=1;
    while(Q.size()){
        int x=Q.front();Q.pop();
        for(int i=head[x];i;i=Next[i]){
            int y=ver[i];
            if(d[y])continue;
            d[y]=d[x]+1;
            f[y][0]=x;
            for(int j=1;j<=t;++j)
                f[y][j]=f[f[y][j-1]][j-1];
            Q.push(y);
        }
    }
}
int lca(int x,int y){
    if(d[x]>d[y])swap(x,y);
    for(int i=t;i>=0;--i)
        if(d[f[y][i]]>=d[x])y=f[y][i];
    if(x==y)return x;
    for(int i=t;i>=0;--i)
        if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
    return f[x][0];
}
int ask(int l,int r,int x,int y,int z,int Z,int k){
    if(l==r)return l;
    int sum=T[T[x].l].sum+T[T[y].l].sum-T[T[z].l].sum-T[T[Z].l].sum;
    int mid=(l+r)/2;
    if(sum>=k)return ask(l,mid,T[x].l,T[y].l,T[z].l,T[Z].l,k);
    else return ask(mid+1,r,T[x].r,T[y].r,T[z].r,T[Z].r,k-sum);
}
int main(){
    cin>>n>>m;
    t=(int)(log(n)/log(2))+1;
    for(int i=1;i<=n;++i)scanf("%d",&A[i]),V.push_back(A[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    int x,y,z;
    for(int i=1;i<n;++i)scanf("%d%d",&x,&y),add(x,y),add(y,x);
    build(1,n,R[1],R[0],getid(A[1]));
    dfs(1,0);
    bfs();
    while(m--){
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",V[ask(1,n,R[x],R[y],R[fa[lca(x,y)]],R[lca(x,y)],z)-1]);
    }
}