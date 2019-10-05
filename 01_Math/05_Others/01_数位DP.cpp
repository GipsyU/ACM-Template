int a[20];
ll dp[20][state];
ll dfs(int pos,,bool lead,bool limit){
    if(pos==-1) return 1;
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];
    int up=limit?a[pos]:9;
    ll ans=0;
    for(int i=0;i<=up;i++){
        ans+=dfs(pos-1,,lead && i==0,limit && i==a[pos])
    }
    if(!limit && !lead) dp[pos][state]=ans;
    return ans;
}
ll solve(ll x){
    int pos=0;
    while(x){
        a[pos++]=x%10;
        x/=10;
    }
    return dfs(pos-1, ,true,true);
}
int main(){
    ll l,r;
    while(~scanf("%lld%lld",&l,&r)){
        memset(dp,-1,sizeof dp);
        printf("%lld\n",solve(r)-solve(l-1));
    }
}
