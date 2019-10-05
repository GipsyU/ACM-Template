namespace IO {
    const int MX = 4e7; //1e7 占用内存 11000kb
    char buf[MX]; int c, sz;
    void Begin() {
        c = 0;
        sz = fread(buf, 1, MX, stdin);//一次性全部读入
    }
    inline bool Read(int &t) {
        while (c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9')) c++;
        if (c >= sz) return false;//若读完整个缓冲块则退出
        bool flag = 0; if(buf[c] == '-') flag = 1, c++;
        for(t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++) t = t * 10 + buf[c] - '0';
        if(flag) t = -t;
        return true;
    }
}