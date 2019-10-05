#include<bits/stdc++.h>
using namespace std;
const int N=,M=,inf=1<<30;
struct DINIC{
    int Next[M],d[N],head[N],ver[M],edge[M],tot,S,T;
    queue<int> q;
    void add(int x,int y,int z){
        ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
        ver[++tot]=x,edge[tot]=0,Next[tot]=head[y],head[y]=tot;
    }
    void build(){
        tot=1,S=N-2,T=N-1,ans=0;
    }
    bool bfs(){
        memset(d,0,sizeof d);
        while(q.size())q.pop();
        q.push(S);d[S]=1;
        while(q.size()){
            int x=q.front();q.pop();
            for(int i=head[x];i;i=Next[i])
                if(edge[i]&&!d[ver[i]]){
                    q.push(ver[i]);
                    d[ver[i]]=d[x]+1;
                    if(ver[i]==T)return 1;
                }
        }
        return 0;
    }
    int find(int x,int flow){
        if(x==T)return flow;
        int rest=flow,k;
        for(int i=head[x];i&&rest;i=Next[i])
            if(edge[i]&&d[ver[i]]==d[x]+1){
                k=find(ver[i],min(rest,edge[i]));
                if(!k)d[ver[i]]=0;
                edge[i]-=k;
                edge[i^1]+=k;
                rest-=k;
            }
        return flow-rest;
    }
    int dinic(){
        int flow=0,maxflow=0;
        while(bfs())
            while(flow=find(S,inf))maxflow+=flow;
        return maxflow;
    }
}G;
