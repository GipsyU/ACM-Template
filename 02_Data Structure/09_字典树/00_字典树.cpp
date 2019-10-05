struct Trie{
    int T[N*10][2],tot;
    void init(){
        tot=1;
        memset(T,0,sizeof T);
        insert(0);
    }
    void insert(int x){
        int p=1;
        for(int i=1<<30;i;i>>=1){
            int y=(x&i)?1:0;
            if(!T[p][y]) T[p][y]=++tot;
            p=T[p][y];
        }
    }
    int find(int x){
        int p=1,ans=0;
        for(int i=1<<30;i;i>>=1){
            int y=(x&i)?0:1;
            if(T[p][y])ans+=i,p=T[p][y];
            else p=T[p][!y];
        }
        return ans;
    }
}T;
