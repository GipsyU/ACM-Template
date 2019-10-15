int ans[N];
struct Aho_Corasick_Automaton {
    int ch[N][26], f[N], val[N], sz, rt;
    int newnode() { memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = 0; return sz++; }
    void init() { sz = 0, rt = newnode(); }
    inline int idx(char c) { return c - 'a'; };
    int ver[N],Next[N],head[N],tot;
    void add(int x,int y){ver[++tot]=y;Next[tot]=head[x];head[x]=tot;}
    void dfs(int x){
        for(int i=head[x];i;i=Next[i]){
            dfs(ver[i]);val[x]+=val[ver[i]];
        }
    }
    void insert(const char* s,int pos) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        ans[pos]=u;
    }
    void build() {
        queue<int> q; f[rt] = rt;
        for (int c = 0; c < 26; c++) {
            if (~ch[rt][c])f[ch[rt][c]] = rt, add(rt,ch[rt][c]), q.push(ch[rt][c]);
            else ch[rt][c] = rt;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                if (~ch[u][c]) f[ch[u][c]] = ch[f[u]][c], add(ch[f[u]][c],ch[u][c]), q.push(ch[u][c]);
                else ch[u][c] = ch[f[u]][c];
            }
        }
    }
    int query(const char* s) {
        int u = rt;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]); u = ch[u][c];
            val[u]++;
        }
        return 0;
    }
 
} aca;
char s[N];
int main(){
    int n;while(cin>>n&&n){
        aca.init();memset(ans,0,sizeof ans);
        for(int i=1;i<=n;++i)scanf("%s",s),aca.insert(s,i);
        aca.build();scanf("%s",s);aca.query(s);
        aca.dfs(aca.rt);
        for(int i=1;i<=n;++i)printf("%d\n",aca.val[ans[i]]);
    }
}