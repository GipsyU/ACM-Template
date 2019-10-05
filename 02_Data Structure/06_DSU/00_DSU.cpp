// ---
// 计算每个点的所有子树中颜色出现最多的颜色\\
// 如果颜色出现次数一样，就颜色累加
// ---
#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
typedef long long ll;
const int N=2e5+10;ll ans[N];
int A[N],ver[N],Next[N],head[N],dsu[N],mx[N],sz[N],tot,t;
unordered_map<int,int> a[N]; 
void add(int x,int y){
	ver[++tot]=y;Next[tot]=head[x];head[x]=tot;
}
void dfs1(int x=1,int y=-1){
	sz[x]=1;
	for(int i=head[x];i;i=Next[i])
		if(ver[i]!=y)dfs1(ver[i],x),sz[x]+=sz[ver[i]];
}
void relax(int x,int y,int z){
	if(z==mx[x])ans[x]+=y;
	if(z>mx[x])ans[x]=y,mx[x]=z;
}
void mrg(int x,int y,int z){
	for(auto& i : a[z]){
		a[y][i.X]+=i.Y;
		relax(x,i.X,a[y][i.X]);
	}
}
void dfs2(int x=1,int y=-1){
	if(sz[x]==1){
		dsu[x]=++t;a[t][A[x]]=1;mx[x]=1;ans[x]=A[x];return;
	}
	int big=0,ma=0;
	for(int i=head[x];i;i=Next[i]){
		if(ver[i]!=y){
			dfs2(ver[i],x);
			if(sz[ver[i]]>ma)ma=sz[ver[i]],big=ver[i];
		}
	}
	dsu[x]=dsu[big];mx[x]=mx[big];ans[x]=ans[big];
	for(int i=head[x];i;i=Next[i]){
		if(ver[i]!=big&&ver[i]!=y){
			mrg(x,dsu[x],dsu[ver[i]]);
		}
	}
	a[dsu[x]][A[x]]++;relax(x,A[x],a[dsu[x]][A[x]]);
}
int main(){
	ios::sync_with_stdio(0);
	int n,x,y;cin>>n;
	for(int i=1;i<=n;++i)cin>>A[i];
	for(int i=1;i<n;++i)cin>>x>>y,add(x,y),add(y,x);
	dfs1();dfs2();
	for(int i=1;i<=n;++i)cout<<ans[i]<<" ";
}