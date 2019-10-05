// ---
// W*W的矩阵，初始值S.修改操作数M<=160000,询问数Q<=10000,W<=2000000\\
// 输入1:把(x,y)的格子增加a\\
// 输入2:输出以左下角为(x1,y1),右上角为(x2,y2)的矩阵的权值和
// ---
#define maxn 200005
int s,w,n,cnt;
int ans[10005],sum[2000005];
struct data{int x,y,z,pos,id;}a[maxn],b[maxn];
inline bool cmp(data a,data b){
    if (a.x==b.x&&a.y==b.y) return a.pos<b.pos;
    else if (a.x==b.x) return a.y<b.y;
    else return a.x<b.x;
}
inline void add(int x,int v){
    for(int i=x;i<=w;i+=i&(-i)) sum[i]+=v;
}
inline int query(int x){
    int ret=0;
    for(int i=x;i;i-=i&(-i)) ret+=sum[i];
    return ret;
}
inline void solve(int l,int r){
    if (l==r) return;
    int mid=(l+r)/2,l1=l,l2=mid+1; 
    for(int i=l;i<=r;++i){
        if (a[i].id<=mid&&!a[i].pos) add(a[i].y,a[i].z);
        if (a[i].id>mid&&a[i].pos) ans[a[i].pos]+=query(a[i].y)*a[i].z;
    }
    for(int i=l;i<=r;++i) if (a[i].id<=mid&&!a[i].pos) add(a[i].y,-a[i].z);
    for(int i=l;i<=r;++i){
        if (a[i].id<=mid) b[l1++]=a[i];
        else b[l2++]=a[i];
    }
    for(int i=l;i<=r;++i) a[i]=b[i];
    solve(l,mid);solve(mid+1,r);
}
int main(){
    read(s);read(w);
    while(1){
        int opt;read(opt);
        if (opt==1){
            int x,y,z;read(x),read(y),read(z);
            n++;a[n]=(data){x,y,z,0,n};
        }
        else if (opt==2){
            int x1,x2,y1,y2;read(x1),read(y1),read(x2),read(y2);--x1,--y1;
            ans[++cnt]=(x2-x1)*(y2-y1)*s;
            n++;a[n]=(data){x1,y1,1,cnt,n};
            n++;a[n]=(data){x1,y2,-1,cnt,n};
            n++;a[n]=(data){x2,y1,-1,cnt,n};
            n++;a[n]=(data){x2,y2,1,cnt,n};
        }
        else break;
    }
    sort(a+1,a+n+1,cmp);
    solve(1,n);
    for(int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
}

