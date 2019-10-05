#include<bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-15, pi = acos(-1);
int sign(db x) {return x < -eps ? -1 : x > eps;}
int cmp(db x, db y) {return sign(x - y);}
int intersect(db l1, db r1, db l2, db r2) {
    if (l1 > r1) swap(l1, r1); if (l2 > r2) swap(l2, r2); return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
}
int inmid(db k1, db k2, db k3) {return sign(k1 - k3) * sign(k2 - k3) <= 0;}//k3 in [k1,k2]?1:0
struct Point {
    db x, y;
    Point operator + (const Point & a)const {return Point{a.x + x, a.y + y};}
    Point operator - (const Point & a)const {return Point{x - a.x, y - a.y};}
    Point operator * (db a) const {return Point{x * a, y * a};}
    Point operator / (db a) const {return Point{x / a, y / a};}
    bool operator < (const Point p) const {int a = cmp(x, p.x); if (a) return a == -1; return cmp(y, p.y) == -1;}
    bool operator == (const Point & a) const {return cmp(x, a.x) == 0 && cmp(y, a.y) == 0;}
    db abs() {return sqrt(x * x + y * y);}
    db abs2() {return x * x + y * y;}
    db dis(Point p) {return ((*this) - p).abs();}
    db dis2(Point p) {return ((*this) - p).abs2();}
    Point turn90() {return (Point) { -y, x};}
    Point unit() {db w = abs(); return (Point) {x / w, y / w};}
    int getP() const {return sign(y) == 1 || (sign(y) == 0 && sign(x) == -1);}
    void input() {scanf("%lf%lf", &x, &y);}
};
typedef vector<Point> VP;
db cross(Point p1, Point p2) {return p1.x * p2.y - p1.y * p2.x;}
db cross(Point p0, Point p1, Point p2) {return cross(p1 - p0, p2 - p0);}
db dot(Point p1, Point p2) {return p1.x * p2.x + p1.y * p2.y;}
db rad(Point p1, Point p2) {return atan2(cross(p1, p2), dot(p1, p2));}
int inmid(Point k1, Point k2, Point k3) {return inmid(k1.x, k2.x, k3.x) && inmid(k1.y, k2.y, k3.y);}
bool compareangle(Point p1, Point p2) {//Polar Angle Sort
    return p1.getP() < p2.getP() || (p1.getP() == p2.getP() && sign(cross(p1, p2)) > 0);
}
int clockwise(Point p1, Point p2, Point Point3) { // p1 p2 Point3 anticlockwise:1 clockwise:-1 others:0
    return sign(cross(p1, p2, Point3));
}
struct Line {
    Point s, e;
    void input() {scanf("%lf%lf%lf%lf", &s.x, &s.y, &e.x, &e.y);}
    Point vec() {return e - s;}
    Point unit() {return vec() / length();}
    db length() {return sqrt(dot(s - e, s - e));}
    db length2() {return dot(s - e, s - e);}
};
int onS(Line l, Point p) {// On Seg?
    return inmid(l.s, l.e, p) && sign(cross(l.s - p, l.e - l.s)) == 0;
}
bool checkLL(Line l1, Line l2) {
    return cmp(cross(l1.s, l2.s, l2.e), cross(l1.e, l2.s, l2.e)) != 0;
}
bool checkLS(Line l1, Line l2) {//Intersection of Line l1 and Seg l2?
    return sign(cross(l2.s, l1.s, l1.e)) * sign(cross(l2.e, l1.s, l1.e)) <= 0;
}
int checkSS(Line l1, Line l2) {//Intersection of Two Seg?1:0
    return intersect(l1.s.x, l1.e.x, l2.s.x, l2.e.x) && intersect(l1.s.y, l1.e.y, l2.s.y, l2.e.y) && checkLS(l1, l2) && checkLS(l2, l1);
}
Point project(Line l, Point p) {
    return l.s + l.vec() * dot(p - l.s, l.vec()) / l.length2();
}
Point reflect(Line l, Point p) {//Mirror Point
    return project(l, p) * 2 - p;
}
Point getLL(Line l1, Line l2) {//Intersection Point of Line l1,l2
    db w1 = cross(l2.s, l1.s, l2.e), w2 = cross(l2.s, l2.e, l1.e); return (l1.s * w2 + l1.e * w1) / (w1 + w2);
}
db disSP(Line l, Point p) {
    Point p2 = project(l, p);
    if (inmid(l.s, l.e, p2)) return p.dis(p2); else return min(p.dis(l.s), p.dis(l.e));
}
db disSS(Line l1, Line l2) {
    if (checkSS(l1, l2)) return 0;
    return min(min(disSP(l1, l2.s), disSP(l1, l2.e)), min(disSP(l2, l1.s), disSP(l2, l1.e)));
}
db area(vector<Point> A) {//Anticlockwise
    db ans = 0;
    for (int i = 0; i < A.size(); i++) ans += cross(A[i], A[(i + 1) % A.size()]);
    return ans / 2;
}
int contain(VP A, Point p) {//2:in 1:on 0:out
    int ans = 0; A.push_back(A[0]);
    for (int i = 1; i < A.size(); i++) {
        Line l = {A[i - 1], A[i]};
        if (onS(l, p)) return 1; if (cmp(l.s.y, l.e.y) > 0) swap(l.s, l.e);
        if (cmp(l.s.y, p.y) >= 0 || cmp(l.e.y, p.y) < 0) continue;
        if (sign(cross(l.e, l.s, p)) < 0)ans ^= 1;
    }
    return ans << 1;
}
bool checkConvex(VP A) { //anticlock
    int n = A.size(); A.push_back(A[0]); A.push_back(A[1]);
    for (int i = 0; i < n; i++) if (sign(cross(A[i], A[i + 1], A[i + 2])) == -1) return 0;
    return 1;
}
VP ConvexHull(VP A, int flag = 1) { // flag=0 不严格 flag=1 严格
    int n = A.size(); VP ans(n * 2);
    sort(A.begin(), A.end()); int now = 0; if (n <= 1)return A;
    for (int i = 0; i < n; ans[now++] = A[i++])
        while (now > 1 && sign(cross(ans[now - 2], ans[now - 1], A[i])) < flag)--now;
    for (int i = n - 2, pre = now; i >= 0; ans[now++] = A[i--])
        while (now > pre && sign(cross(ans[now - 2], ans[now - 1], A[i])) < flag)--now;
    ans.resize(now - 1); return ans;
}
db ConvexDiameter(VP A) {
    int n = A.size(); if (n <= 1)return 0;
    int is = 0, js = 0; for (int k = 1; k <= n; ++k)is = A[k] < A[is] ? k : is, js = A[js] < A[k] ? k : js;
    int i = is, j = js; db ret = A[i].dis(A[j]); do {
        if (sign(cross(A[(i + 1) % n] - A[i], A[(j + 1) % n] - A[j])) >= 0)(++j) %= n;
        else (++i) %= n;
        ret = max(ret, A[i].dis(A[j]));
    } while (i != is || j != js);
    return ret;
}
VP ConvexCut(VP A, Line l) { // 保留 k1,k2,p 逆时针的所有点,判断n是否为0
    int n = A.size(); A.push_back(A[0]); VP ans;
    for (int i = 0; i < n; i++) {
        int w1 = clockwise(l.s, l.e, A[i]), w2 = clockwise(l.s, l.e, A[i + 1]);
        if (w1 >= 0) ans.push_back(A[i]);
        if (w1 * w2 < 0) ans.push_back(getLL(l, Line{A[i], A[i + 1]}));
    }
    return ans;
}
struct Circle {
    Point o; db r;
    void input() {o.input(); scanf("%lf", &r);}
    int inside(Point k) {return cmp(r, o.dis(k));}
};
int checkCC(Circle c1, Circle c2) {// 返回两个圆的公切线数量
    db d = c1.o.dis(c2.o); if (cmp(d, c1.r + c2.r) == 1)return 4;
    if (cmp(d, c1.r + c2.r) == 0)return 3; if (cmp(d, abs(c1.r - c2.r)) == 1)return 2;
    if (cmp(d, abs(c1.r - c2.r)) == 0)return 1; return 0;
}
vector<Point> getCL(Circle c, Line l) {// 沿着 s->e 方向给出 , 相切给出两个
    Point p = project(l, c.o); db d = c.r * c.r - p.dis2(c.o);
    if (sign(d) == -1)return{};
    Point del = l.vec() / l.length() * sqrt(max(db(0.0), d)); return {p - del, p + del};
}
vector<Point> getCC(Circle c1, Circle c2) { // 沿圆 c1 逆时针给出 , 相切给出两个
    int pd = checkCC(c1, c2); if (pd == 0 || pd == 4) return {};
    db a = c1.o.dis2(c2.o), cosA = (c1.r * c1.r + a - c2.r * c2.r) / (2 * c1.r * sqrt(max(a, (db)0.0)));
    db b = c1.r * cosA, c = sqrt(max((db)0.0, c1.r * c1.r - b * b));
    Point k = Line{c1.o, c2.o} .unit(), m = c1.o + k * b, del = k.turn90() * c;
    return {m - del, m + del};
}
vector<Point> TangentCP(Circle c, Point p) {
    db x = c.o.dis2(p), d = x - c.r * c.r; if (sign(d) < 0)return{};
    Point p1 = c.o + (p - c.o) * (c.r * c.r / x), p2 = (p - c.o).turn90() * (c.r * sqrt(d) / x);
    return {p1 - p2, p1 + p2};//counter clock-wise
}
db areaCT(Circle c, Line l) { // 圆与有向三角形的面积交
    l.s = l.s - c.o, l.e = l.e-c.o, c.o = c.o - c.o;
    int pd1 = c.inside(l.s), pd2 = c.inside(l.e);
    vector<Point>A = getCL(c, l);
    if (pd1 >= 0) {
        if (pd2 >= 0) return cross(l.s, l.e) / 2;
        return c.r * c.r * rad(A[1], l.e) / 2 + cross(l.s, A[1]) / 2;
    } else if (pd2 >= 0) {
        return c.r * c.r * rad(l.s, A[0]) / 2 + cross(A[0], l.e) / 2;
    } else {
        int pd = cmp(c.r, disSP(l, c.o));
        if (pd <= 0) return c.r * c.r * rad(l.s, l.e) / 2;
        return cross(A[0], A[1]) / 2 + c.r * c.r * (rad(l.s, A[0]) + rad(A[1], l.e)) / 2;
    }
}
Circle getcircle(Point k1, Point k2, Point k3) { //检查是否共线
    db a1 = k2.x - k1.x, b1 = k2.y - k1.y, c1 = (a1 * a1 + b1 * b1) / 2;
    db a2 = k3.x - k1.x, b2 = k3.y - k1.y, c2 = (a2 * a2 + b2 * b2) / 2;
    db d = a1 * b2 - a2 * b1;
    Point o = (Point) {k1.x + (c1 * b2 - c2 * b1) / d, k1.y + (a1 * c2 - a2 * c1) / d};
    return (Circle) {o, k1.dis(o)};
}
Circle minC(vector<Point> A) {
    random_shuffle(A.begin(), A.end()); Circle ans = (Circle) {A[0], 0};
    for (int i = 1; i < A.size(); i++)
        if (ans.inside(A[i]) == -1) {
            ans = (Circle) {A[i], 0};
            for (int j = 0; j < i; j++)
                if (ans.inside(A[j]) == -1) {
                    ans.o = (A[i] + A[j]) / 2; ans.r = ans.o.dis(A[i]);
                    for (int k = 0; k < j; k++)
                        if (ans.inside(A[k]) == -1)ans = getcircle(A[i], A[j], A[k]);
                }
        }
    return ans;
}
struct Point3 {
    db x, y, z;
    Point3 operator + (Point3 a) {return (Point3) {x + a.x, y + a.y, z + a.z};}
    Point3 operator - (Point3 a) {return (Point3) {x - a.x, y - a.y, z - a.z};}
    Point3 operator * (db a) {return (Point3) {x*a, y*a, z*a};}
    Point3 operator / (db a) {return (Point3) {x / a, y / a, z / a};}
    db abs2() {return x * x + y * y + z * z;}
    db abs() {return sqrt(x * x + y * y + z * z);}
    db dis(Point3 a) {return ((*this) - a).abs();}
    void input() {scanf("%lf%lf%lf", &x, &y, &z);}
};
Point3 cross(Point3 k1, Point3 k2) {
    return (Point3) {k1.y*k2.z - k1.z*k2.y, k1.z*k2.x - k1.x*k2.z, k1.x*k2.y - k1.y*k2.x};
}
db dot(Point3 k1, Point3 k2) {return k1.x * k2.x + k1.y * k2.y + k1.z * k2.z;}
db rand_db() {return 1.0 * rand() / RAND_MAX;}
typedef vector<Point3> VP3; typedef vector<VP3> VVP3;
db minSphere(VP3 A) {
    double step = 10000, ans = 1e30, mt;
    Point3 p = Point3{0, 0, 0}; int s = 0;
    while (step > eps) {
        for (int i = 0; i < A.size(); i++)if (p.dis(A[s]) < p.dis(A[i]))s = i;
        mt = p.dis(A[s]); ans = min(ans, mt);
        p = p + (A[s] - p) / mt * step; step *= 0.98;
    }
    return ans;
}
db getV(Point3 k1, Point3 k2, Point3 k3, Point3 k4) { // get the Volume
    return dot(cross(k2 - k1, k3 - k1), k4 - k1);
}
namespace CH3 {
    VVP3 ret; set<pair<int, int> >e;
    int n; VP3 p, q;
    void wrap(int a, int b) {
        if (e.find({a, b}) == e.end()) {
            int c = -1;
            for (int i = 0; i < n; i++) if (i != a && i != b) {
                    if (c == -1 || sign(getV(q[c], q[a], q[b], q[i])) > 0) c = i;
                }
            if (c != -1) {
                ret.push_back({p[a], p[b], p[c]});
                e.insert({a, b}); e.insert({b, c}); e.insert({c, a});
                wrap(c, b); wrap(a, c);
            }
        }
    }
    VVP3 ConvexHull3D(VP3 _p) {
        p = q = _p; n = p.size();
        ret.clear(); e.clear();
        for (auto &i : q) i = i + (Point3) {rand_db() * 1e-4, rand_db() * 1e-4, rand_db() * 1e-4};
        for (int i = 1; i < n; i++) if (q[i].x < q[0].x) swap(p[0], p[i]), swap(q[0], q[i]);
        for (int i = 2; i < n; i++) 
            if ((q[i].x - q[0].x) * (q[1].y - q[0].y) > (q[i].y - q[0].y) * (q[1].x - q[0].x)) 
                swap(q[1], q[i]), swap(p[1], p[i]);
        wrap(0, 1);
        return ret;
    }
}
db volume(VVP3 A) {
    if (A.size() == 0) return 0; Point3 p = A[0][0]; db ans = 0;
    for (VP3 nowF : A)
        for (int i = 2; i < nowF.size(); i++)
            ans += abs(getV(p, nowF[0], nowF[i - 1], nowF[i]));
    return ans / 6;
}
db area(VP3 A){
    if(A.size()<3)return 0;db ans=0;
    for(int i=2;i<A.size();++i)ans+=cross(A[i-1]-A[0],A[i]-A[0]).abs();
    return abs(ans/2);
}
db surface_area(VVP3 A){
    if(A.size()==0)return 0;db ans=0;
    for(VP3 i:A)ans+=area(i);return ans;
}