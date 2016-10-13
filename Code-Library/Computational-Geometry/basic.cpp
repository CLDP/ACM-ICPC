const int MAXN = 10010;
const double EPS = 1e-8;
const double PI = acos(-1.0);

struct CPoint { double x, y; };
double sqr(double x) { return x * x; }
int dcmp(double x) {
    if (x < -EPS) return -1; else return (x > EPS);
}
double cross(CPoint p0, CPoint p1, CPoint p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
double dot(CPoint p0, CPoint p1, CPoint p2) {
    return (p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y);
}
double dissqr(CPoint p1, CPoint p2) {
    return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}
double dis(CPoint p1, CPoint p2) {
    return sqrt(dissqr(p1, p2));
}
int PointEqual(const CPoint &p1, const CPoint &p2) {
    return dcmp(p1.x - p2.x) == 0 && dcmp(p1.y - p2.y) == 0;
}
