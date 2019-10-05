// ---
// 题意：给一棵树，并给定各个点权的值，然后有3种操作：\\
// I D C1 C2 K: 把C1与C2的路径上的所有点权值加减K\\
// Q C：查询节点编号为C的权值
// ---
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+100;
int head[N],Next[N],ver[N],siz[N],son[N],
c[N],dp[N],fa[N],dep[N],pos[N],top[N],A[N];
int tot,sz;
void add(int x,int y){
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
}
void dfs1(int x){
    son[x]=0,siz[x]=1;
    for(int i=head[x];i;i=Next[i]){
        int y=ver[i];
        if(y==fa[x]) continue;
        fa[y]=x;
        dep[y]=dep[x]+1;
        dfs1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[son[x]]) son[x]=y;
    }
}
void dfs2(int x,int tp){
    pos[x]=++sz;
    top[x]=tp;
    if(son[x]) dfs2(son[x],top[x]);
    for(int i=head[x];i;i=Next[i]){
        int y=ver[i];
        if(y!=son[x]&&y!=fa[x])
            dfs2(y,y);
    }
}
int lowbit(int x){
    return x&(-x);
}
void Add(int x,int val){
    for(;x<=N;x+=lowbit(x)) c[x]+=val;
}
int Query(int x){
    int sum=0;
    for(;x;x-=lowbit(x)) sum+=c[x];
    return sum;
}
void update(int x,int y,int z){
    Add(x,z);
    Add(y+1,-z);
}
void change(int x,int y,int z){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(pos[top[x]],pos[x],z);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(pos[x],pos[y],z);
}
int main(){
	int n,m,q;
    while(cin>>n>>m>>q){
        for(int i=0;i<N;++i){
            head[i]=Next[i]=ver[i]=siz[i]=son[i]=
        c[i]=dp[i]=fa[i]=dep[i]=pos[i]=top[i]=A[i]=0;
        }
        tot=sz=0;
        for(int i=1;i<=n;++i) scanf("%d",&A[i]);
        int u,v,k;
        while(m--){
            scanf("%d%d",&u,&v);
            add(u,v);
            add(v,u);
        }
        dfs1(1);
        dfs2(1,1);
        string s;
        while(q--){
            cin>>s;
            if(s[0]=='I'){
                scanf("%d%d%d",&u,&v,&k);
                change(u,v,k);
            }else if(s[0]=='D'){
                scanf("%d%d%d",&u,&v,&k);
                change(u,v,-k);
            }else{
                scanf("%d",&k);
                cout<<Query(pos[k])+A[k]<<endl;
            }
        }
    }
}