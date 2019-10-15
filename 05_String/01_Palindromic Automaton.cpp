struct Palindromic_Automaton {
    int ch[N][26], f[N], len[N], s[N], ok[N];
    int cnt[N]; // 结点表示的本质不同的回文串的个数(调用count()后)
    int num[N]; // 结点表示的最长回文串的最右端点为回文串结尾的回文串个数
    int last, sz, n;
    int newnode(int x) {
        memset(ch[sz], 0, sizeof(ch[sz]));
        cnt[sz] = num[sz] = 0, len[sz] = x;
        return sz++;
    }
    void init() {
        sz = 0; newnode(0), newnode(-1); last = n = 0, s[0] = -1, f[0] = 1;
    }
    int get(int u) {for (; s[n - len[u] - 1] != s[n]; u = f[u]); return u;}
    void add(int c) {
        s[++n] = c;
        int u = get(last);
        if (!ch[u][c]) {
            int np = newnode(len[u] + 2);
            f[np] = ch[get(f[u])][c];
            num[np] = num[f[np]] + 1;
            ch[u][c] = np;
            ok[np]=check(n-len[np]+1,n);
        }
        last = ch[u][c];
        cnt[last]++;
    }
    ll count(){
        ll ans=0;
        for (int i = sz - 1; ~i; i--) cnt[f[i]] += cnt[i];
        for(int i=sz-1;i>1;--i)ans=ans+1ll*cnt[i]*ok[i];
        return ans;
    }
}pam;
int main(){
    pam.init();
    for(int i=0;i<n;++i)pam.add(s[i]-'a');
    cout<<pam.count()<<endl;
}