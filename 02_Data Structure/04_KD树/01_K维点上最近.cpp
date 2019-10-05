// ---
// k维n个点，给定点的最近的m个点
// ---
#include<bits/stdc++.h>
#define SQ(x) (x)*(x)
using namespace std;
const int N=1e5+10;
int idx,k;
struct P{
	int x[5];
	bool operator <(const P &u)const{return x[idx]<u.x[idx];}
}A[N];
typedef pair<int,P> DIS;
priority_queue<DIS>Q;
vector<DIS> V;
struct KDTREE{
	int S[N<<2];P R[N<<2];
	void build(int p,int l,int r,int dep){
		if(l>r)return;
		S[p]=r-l;S[p*2]=S[p*2+1]=-1;
		idx=dep%k;int mid=(l+r)/2;
		nth_element(A+l,A+mid,A+r+1);
		R[p]=A[mid];
		build(p*2,l,mid-1,dep+1);
		build(p*2+1,mid+1,r,dep+1);
	}
	void query(int p,int m,int dep,P a){
		if(S[p]==-1)return;
		DIS tmp=DIS(0,R[p]);
		for(int i=0;i<k;++i)tmp.first+=SQ(tmp.second.x[i]-a.x[i]);
		int l=p*2,r=p*2+1,dim=dep%k,flag=0;
		if(a.x[dim]>=R[p].x[dim])swap(l,r);
		if(~S[l])query(l,m,dep+1,a);
		if(Q.size()<m)Q.push(tmp),flag=1;
		else{
			if(Q.top().first>tmp.first)Q.pop(),Q.push(tmp);
			if(SQ(R[p].x[dim]-a.x[dim])<Q.top().first)flag=1;
		}
		if(~S[r]&&flag)query(r,m,dep+1,a);
	}
}KDT;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m;
	while(cin>>n>>k){
		for(int i=1;i<=n;++i)for(int j=0;j<k;++j)cin>>A[i].x[j];
		KDT.build(1,1,n,0);
		int T;
		cin>>T;
		while(T--){
			P a;
			for(int i=0;i<k;++i)cin>>a.x[i];
			cin>>m;
			KDT.query(1,m,0,a);
			V.clear();
			while(Q.size()){
				V.push_back(Q.top());
				Q.pop();
			}
			printf("the closest %d points are:\n",V.size());
			for(int i=V.size()-1;i>=0;--i){
				printf("%d",V[i].second.x[0]);
				for(int j=1;j<k;++j)printf(" %d",V[i].second.x[j]);
				printf("\n");
			}
		}
	}
}