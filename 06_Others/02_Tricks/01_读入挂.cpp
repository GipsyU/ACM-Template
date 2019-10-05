inline void read(int &x){char ch;bool ok;
for(ok=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') ok=1;
for(x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());if(ok) x=-x;}