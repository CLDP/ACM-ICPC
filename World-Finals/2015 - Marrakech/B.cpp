#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const int MAXN = 210;
const double INF = 1e5;

struct CPoint { 
    double x, y; 
    CPoint() {}
    CPoint(double _x, double _y): x(_x), y(_y) {}
};

double sqr(double x) { 
    return x * x; 
}

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

int PointEqual(const CPoint &p1, const CPoint &p2) {
    return dcmp(p1.x - p2.x) == 0 && dcmp(p1.y - p2.y) == 0;
}

int PointOnSegment(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0 && dcmp(dot(p0, p1, p2)) <= 0;
}

CPoint bp;  // Used for GrahamScan, lowest point

bool PolarCmp(const CPoint &p1, const CPoint &p2) {
    int u = dcmp(cross(bp, p1, p2));
    return u > 0 || (u == 0 && dcmp(dissqr(bp, p1) - dissqr(bp, p2)) < 0);
}

int GrahamScan(CPoint ch[], int n, int &m) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int u = dcmp(ch[i].x - ch[k].x);
        int v = dcmp(ch[i].y - ch[k].y);
        if (v < 0 || (v == 0 && u < 0)) k = i;
    }
    bp = ch[k];
    sort(ch, ch + n, PolarCmp);
    n = unique(ch, ch + n, PointEqual) - ch;
    if (n <= 1) {
        m = n;
        return 0;
    }
    if (dcmp(cross(ch[0], ch[1], ch[n - 1])) == 0) {
        m = 2;
        ch[1] = ch[n - 1];
        return 0;
    }
    ch[n++] = ch[0];
    int i = 1;
    for (int j = 2; j < n; ++j) {
        while (i > 0 && dcmp(cross(ch[i - 1], ch[i], ch[j])) < 0) --i;
        ch[++i] = ch[j];
    }
    m = i;
    for (int i = 0; i < m - 1 - i; ++i) {
        swap(ch[i], ch[m - 1 - i]);
    }
    return 0; 
}

typedef complex<double> point;

inline int dbcmp(double d) { return d < -EPS ? -1 : (d > EPS);}
double operator ^ (point a, point b) { return imag(conj(a) * b);}

struct line {
    point a, b;
    double angle;
    line() {}
    line(point _a, point _b) :a(_a), b(_b) {angle = arg(_b - _a);}
    bool operator < (line const &l) const {
        return dbcmp(angle - l.angle) < 0 ||
               (dbcmp(angle - l.angle) == 0 && dbcmp(b - a ^ l.b - a) < 0);
    }
};

point operator * (const line &u, const line &v) {
    point ret = u.a;
    double t = u.a - v.a ^ v.b - v.a;
    double s = u.a - u.b ^ v.b - v.a;
    return ret + (u.b - u.a) * t / s;
}

point p[MAXN];
line l[MAXN];

bool onLeft(point p1, line u){
    return dbcmp(p1 - u.a ^ u.b - u.a) <= 0;
}

bool uniquecmp(line u, line v){
    return dbcmp(u.angle - v.angle) == 0;
}

// Get the core of half plane and save in l
int gethe(line *l, int lsz, point *p) {
    int e[MAXN];
    int eb = 0, ee = 2, pb = 0, pe = 1, psz = 1;
    sort(l, l + lsz);
    p[lsz] = p[0];
    // left only one for each slope
    lsz = distance(l, unique(l, l + lsz, uniquecmp));
    e[0] = 0;
    e[1] = 1;
    p[0] = l[0] * l[1];
    for (int i = 2; i < lsz; ++i) {
        while (pb != pe && !onLeft(p[pe - 1], l[i])) --pe, --ee;
        while (pb != pe && !onLeft(p[pb], l[i])) ++pb, ++eb;
        p[pe++] = l[i] * l[e[ee - 1]];
        e[ee++] = i;
    }
    while (pb != pe && !onLeft(p[pe - 1], l[e[eb]])) --pe, --ee;
    while (pb != pe && !onLeft(p[pb], l[e[ee - 1]])) ++pb, ++eb;
    p[pe++] = l[e[pb]] * l[e[ee - 1]];
    psz = pe - pb;
    for (int i = 0; pb != pe; ++i) p[i] = p[pb++];
    return psz;
}

double area(point *p, int n) {
    p[n] = p[0];
    double sum = 0;
    for (int i = 0; i < n; ++i) sum += p[i] ^ p[i + 1];
    return fabs(sum) / 2;
}

double half_plane_intersection(CPoint ch1[], int N, CPoint ch2[], int M) {
    ch1[N] = ch1[0];
    ch2[M] = ch2[0];
    for (int i = 0; i < N; ++i) {
        l[i] = line(point(ch1[i + 1].x, ch1[i + 1].y), point(ch1[i].x, ch1[i].y));
    }
    for (int i = 0; i < M; ++i) {
        l[i + N] = line(point(ch2[i + 1].x, ch2[i + 1].y), point(ch2[i].x, ch2[i].y));
    }

    int psz = gethe(l, N + M, p);
    if (psz < 3) return 0;
    return area(p, psz);
}

bool touch(CPoint ch1[], int N, CPoint ch2[], int M) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
         if (PointOnSegment(ch1[i], ch2[j], ch2[(j + 1) % M])) return true;
    }
    for (int j = 0; j < M; ++j) {
        for (int i = 0; i < N; ++i) 
         if (PointOnSegment(ch2[j], ch1[i], ch1[(i + 1) % N])) return true;
    }
    return false;
}

int N, M;
double mx, my;
CPoint X[11], Y[11], Z[22];

int makeZ(double T) {
    for (int i = 0; i < N; ++i) {
        Z[i] = X[i];
        Z[i + N].x = X[i].x + mx * T;
        Z[i + N].y = X[i].y + my * T;
    }
    return 0;
}

int makeS(double T) {
    for (int i = 0; i < N; ++i) {
        Z[i].x = X[i].x + mx * T;
        Z[i].y = X[i].y + my * T;
    }
    return 0;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].y;
    cin >> mx >> my;
    cin >> M;
    for (int i = 0; i < M; ++i) cin >> Y[i].x >> Y[i].y;
    double tx, ty;
    cin >> tx >> ty;
    mx -= tx;
    my -= ty;

    if (fabs(mx) + fabs(my) < EPS) {
        double maxA = half_plane_intersection(X, N, Y, M);
        if (maxA > 0) {
            cout << 0 << endl;
        } else {
            cout << "never" << endl;
        }
        return 0;
    }

    makeZ(INF);

    int NN;
    GrahamScan(Z, N + N, NN);

    double maxA = half_plane_intersection(Z, NN, Y, M);

    if (maxA < EPS) {
        if (!touch(Z, NN, Y, M)) {
            cout << "never" << endl;
            return 0;
        }

        double L = 0, R = INF;
        while (R - L > EPS * R) {
            double mid = (L + R) / 2;
            makeZ(mid);
            GrahamScan(Z, N + N, NN);
            if (!touch(Z, NN, Y, M)) L = mid; else R = mid;
        }
        printf("%.6lf\n", L);
        return 0;
    }

    double l = 0, r = INF;
    double L, R;
    while (r - l > EPS * r) {
        double mid = (l + r) / 2;
        makeZ(mid);
        GrahamScan(Z, N + N, NN);
        if (half_plane_intersection(Z, NN, Y, M) < EPS) l = mid; else r = mid;
    }

    L = l = r;
    r = INF;
    while (r - l > EPS * r) {
        double mid = (l + r) / 2;
        makeZ(mid);
        GrahamScan(Z, N + N, NN);
        if (half_plane_intersection(Z, NN, Y, M) < maxA - EPS) l = mid; else r = mid;
    }

    R = r;

    while (R - L > EPS * R) {
        double mid1 = L + (R - L) / 3;
        double mid2 = R - (R - L) / 3;
        makeS(mid1);
        double area1 = half_plane_intersection(Z, N, Y, M);
        makeS(mid2);
        double area2 = half_plane_intersection(Z, N, Y, M);
        if (area1 > area2) {
            R = mid2;
        } else {
            L = mid1;
        }
    }

    printf("%.6lf\n", L);
    return 0;
}
