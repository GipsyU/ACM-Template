const int N=1e5+10;
struct HisTree{
    int l,r,sum;
}T[N*40];
vector<int> V;
int R[N],A[N],cnt;
int getid(int x){
    return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
}
void build(int l,int r,int &x,int y,int pos){
    T[++cnt]=T[y],T[cnt].sum++,x=cnt;
    if(l==r)return;
    int mid=(l+r)/2;
    if(pos<=mid)build(l,mid,T[x].l,T[y].l,pos);
    else build(mid+1,r,T[x].r,T[y].r,pos);
}
int ask(int l,int r,int x,int y,int k){
    if(l==r)return l;
    int sum=T[T[y].l].sum-T[T[x].l].sum;
    int mid=(l+r)/2;
    if(sum>=k)return ask(l,mid,T[x].l,T[y].l,k);
    else return ask(mid+1,r,T[x].r,T[y].r,k-sum);
}
int main(){
    int n,m,x,y,z;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",&A[i]),V.push_back(A[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    for(int i=1;i<=n;++i)build(1,n,R[i],R[i-1],getid(A[i]));
    while(m--){
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",V[ask(1,n,R[x-1],R[y],z)-1]);
    }
}