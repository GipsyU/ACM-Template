struct Quary{
    int l,r,num;
    bool operator < (const Quary node) const{//奇偶优化
        return (pos[l] < pos[node.l])||(pos[l] == pos[node.l] && (pos[l] & 1 ? r < node.r : r > node.r));
    }
}quary[N];
int pos[N],ans[N],block;
void add(int x)
 
void del(int x)
 
int main(){
    int n,m;
    while(scanf("%d%d", &n, &m) == 2){
        block = sqrt(n);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &ma[i]);
            pos[i] = i / block;
        }
        for(int i = 1; i <= m; i ++){
            int num, l, r;
            scanf("%d%d",&quary[i].l,&quary[i].r);
            quary[i].num = i;
        }
        sort(quary + 1, quary + m + 1);
        l = 1;
        r = 0;
        for(int i = 1; i <= m; i ++){
            while(l > quary[i].l){
                l --;
                add(l);
            }
            while(r < quary[i].r){
                r ++;
                add(r);
            }
            while(l < quary[i].l){
                del(l);
                l ++;
            }
            while(r > quary[i].r){
                del(r);
                r --;
            }
            ans[quary[i].num] = ask(quary[i]);
        }
    }
}