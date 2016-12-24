#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const int MAXN = 210;
const double INF = 2 * 1e4;

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

typedef CPoint Vector;

struct Line {
    // point on the line
    CPoint p;
    // direction
    Vector v;
    // angle from x+ to vector v
    double ang;
    Line() {}
    Line(CPoint p, Vector v): p(p), v(v) {ang = atan2(v.y, v.x);}
    bool operator < (const Line &L) const {
        return ang < L.ang;
    }
};
Vector operator + (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}
Vector operator - (CPoint A, CPoint B) {
    return Vector(A.x - B.x, A.y - B.y);
}
Vector operator * (Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}
Vector operator / (Vector A, double p) {
    return Vector(A.x / p, A.y / p);
}
double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}
bool OnLeft(Line L, CPoint P) {
    return Cross(L.v, P - L.p) > 0;
}
CPoint GetIntersection(Line a, Line b) {
    Vector u = a.p - b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v * t;
}

int HalfplaneIntersection(Line *L, int n, CPoint *poly) {
    sort(L, L + n);
    int first = 0, last = 0;
    CPoint *p = new CPoint[n];
    Line *q = new Line[n];
    q[0] = L[0];
    for (int i = 1; i < n; ++i) {
        while (first < last && !OnLeft(L[i], p[last - 1])) --last;
        while (first < last && !OnLeft(L[i], p[first])) ++first;
        q[++last] = L[i];
        if (fabs(Cross(q[last].v, q[last - 1].v)) < EPS) {
            // Two parallel lines, same direction
            --last;
            if (OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if (first < last) p[last - 1] = GetIntersection(q[last - 1], q[last]);
    }
    // Remove useless half planes
    while (first < last && !OnLeft(q[first], p[last - 1])) --last;
    // Need to add four boundary lines to make this correct
    // Or if you know the given region is bounded
    if (last - first <= 1) return 0; 
    p[last] = GetIntersection(q[last], q[first]);

    int m = 0;
    for (int i = first; i <= last; ++i) poly[m++] = p[i];
    delete[] p;
    delete[] q;
    return m;
}

double PolygonArea(CPoint *p, int n) {
    double area = 0;
    for (int i = 1; i < n - 1; ++i) area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return fabs(area) / 2;
}


int N, M;
double mx, my;
CPoint X[11], Y[11], Z[22];
Line L[MAXN];
CPoint P[MAXN];

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

double half_plane_intersection(CPoint ch1[], int N, CPoint ch2[], int M) {
    ch1[N] = ch1[0];
    ch2[M] = ch2[0];
    for (int i = 0; i < N; ++i) {
        L[i] = Line(ch1[i], ch1[i] - ch1[i + 1]);
    }
    for (int i = 0; i < M; ++i) {
        L[i + N] = Line(ch2[i], ch2[i] - ch2[i + 1]);
    }

    int m = HalfplaneIntersection(L, N + M, P);
    if (!m) return 0;
    return PolygonArea(P, m);
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
