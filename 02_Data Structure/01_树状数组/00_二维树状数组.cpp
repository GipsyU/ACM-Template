const int N =;
int c[N+2][N+2];
int lowbit (int i) {
    return i & (-i);
}
void add (int x, int y, int value) {
    while (x <= N) {
        int i = y;
        while (i <= N) {
            c[x][i] += value;
            i += lowbit (i);
        }
        x += lowbit (x);
    }
}
int sum (int x, int y) {
    int sum = 0;
    while (x > 0) {
        int i = y;
        while (i > 0) {
            sum += c[x][i];
            i -= lowbit (i);
        }
        x -= lowbit (x);
    }
    return sum;
}