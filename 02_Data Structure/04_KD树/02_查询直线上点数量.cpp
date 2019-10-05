// ---
// n个点，m个直线，问每条直线上有几个点
// ---
#include<cstdio>
#include<algorithm>
const int N=100010;
using namespace std;
typedef long long ll;
int Case,n,m,i,root,cmp_d,ans,A,B;
ll LB,LA,LC;
struct node{
    int d[2];
    int l,r;
    int Max[2],Min[2];
    int sum;
}t[N];
inline bool cmp(const node&a,const node&b){
    return a.d[cmp_d]<b.d[cmp_d];
}
inline void umax(int&a,int b){if(a<b)a=b;}
inline void umin(int&a,int b){if(a>b)a=b;}
inline void up(int x){
    if(t[x].l){
        umax(t[x].Max[0],t[t[x].l].Max[0]);
        umin(t[x].Min[0],t[t[x].l].Min[0]);
        umax(t[x].Max[1],t[t[x].l].Max[1]);
        umin(t[x].Min[1],t[t[x].l].Min[1]);
    }
    if(t[x].r){
        umax(t[x].Max[0],t[t[x].r].Max[0]);
        umin(t[x].Min[0],t[t[x].r].Min[0]);
        umax(t[x].Max[1],t[t[x].r].Max[1]);
        umin(t[x].Min[1],t[t[x].r].Min[1]);
    }
}
int build(int l,int r,int D){
    int mid=(l+r)>>1;
    cmp_d=D;
    nth_element(t+l+1,t+mid+1,t+r+1,cmp);
    t[mid].Max[0]=t[mid].Min[0]=t[mid].d[0];
    t[mid].Max[1]=t[mid].Min[1]=t[mid].d[1];
    t[mid].sum=1;
    if(l!=mid)t[mid].l=build(l,mid-1,!D);else t[mid].l=0;
    if(r!=mid)t[mid].r=build(mid+1,r,!D);else t[mid].r=0;
    up(mid);
    return mid;
}
inline bool check(int xl,int xr,int yl,int yr){
    ll t=-LB*xl+LC;
    if(LA*yl<=t&&t<=LA*yr)return 1;
    t=-LB*xr+LC;
    if(LA*yl<=t&&t<=LA*yr)return 1;
    t=-LA*yl+LC;
    if(LB*xl<=t&&t<=LB*xr)return 1;
    t=-LA*yr+LC;
    if(LB*xl<=t&&t<=LB*xr)return 1;
    return 0;
}
void ask(int x){
    if(!check(t[x].Min[0],t[x].Max[0],t[x].Min[1],t[x].Max[1]))return;
    if(LB*t[x].d[0]+LA*t[x].d[1]==LC)ans++;
    if(t[x].l)ask(t[x].l);
    if(t[x].r)ask(t[x].r);
}
int main(){
    scanf("%d",&Case);
    while(Case--){
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)scanf("%d%d",&t[i].d[0],&t[i].d[1]);
        root=build(1,n,0);
        while(m--){
            scanf("%d%d",&A,&B);//(a,0) (0,b)
            LA=A;
            LB=B;
            LC=LA*LB;
            ans=0;
            ask(root);
            printf("%d\n",ans);
        }
    }
}