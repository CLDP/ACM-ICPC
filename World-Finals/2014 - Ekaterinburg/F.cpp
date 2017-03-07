#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAXN = 50010;
const double INF = 1e100;
const double EPS = 1e-6;
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
int PointOnLine(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0;
}
int PointOnSegment(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0 && dcmp(dot(p0, p1, p2)) <= 0;
}
double PointToLine(CPoint p0, CPoint p1, CPoint p2, CPoint &cp) {
    double d = dis(p1, p2), s = cross(p1, p2, p0) / d;
    cp.x = p0.x + s * (p2.y - p1.y) / d;
    cp.y = p0.y - s * (p2.x - p1.x) / d;
    return fabs(s);
}

struct Event {
    int xp, yp;
    CPoint X, Y;
    Event(): xp(1), yp(1) {}
};

int N, M;
CPoint X[MAXN], Y[MAXN];

CPoint moveP(CPoint X, CPoint Y, double T) {
    CPoint Z = X;
    double D = dis(X, Y);
    Z.x += (Y.x - X.x) * T / D;
    Z.y += (Y.y - X.y) * T / D;
    return Z;
}

CPoint segment(CPoint X, CPoint Y) {
    CPoint Z;
    Z.x = Y.x - X.x;
    Z.y = Y.y - X.y;
    return Z;
}

bool check(Event E, double T) {
    double TT = T;
    while (T > 0) {
        double D = dis(E.Y, Y[E.yp]);
        if (T < D) {
            E.Y = moveP(E.Y, Y[E.yp], T);
            T = 0;
            break;
        } else {
            T -= D;
            E.Y = Y[E.yp];
            ++E.yp;
        }
    }

    CPoint O;
    O.x = O.y = 0;
    double minD = INF;
    while (E.xp < N && E.yp < M) {
        double D1 = dis(E.X, X[E.xp]);
        double D2 = dis(E.Y, Y[E.yp]);
        CPoint P1, P2;
        if (D1 > D2) {
            P1 = moveP(E.X, X[E.xp], D2);
            P2 = Y[E.yp];
            ++E.yp;
        } else {
            P1 = X[E.xp];
            P2 = moveP(E.Y, Y[E.yp], D1);
            ++E.xp;
        }

        CPoint S1 = segment(E.X, E.Y);
        CPoint S2 = segment(P1, P2);
        minD = min(minD, dis(O, S1));
        minD = min(minD, dis(O, S2));
        CPoint SS;
        double DD = PointToLine(O, S1, S2, SS);
        if (PointOnSegment(SS, S1, S2)) minD = min(minD, DD);

        E.X = P1;
        E.Y = P2;
    }
    return minD <= TT;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].y;
    cin >> M;
    for (int i = 0; i < M; ++i) cin >> Y[i].x >> Y[i].y;
    double L = 0, R = 0;
    for (int i = 0; i + 1 < M; ++i) R += dis(Y[i], Y[i + 1]);

    if (dis(X[0], Y[M - 1]) > R + EPS) {
        cout << "impossible" << endl;
        return 0;
    }
    while (L + EPS < R) {
        double mid = (L + R) / 2;
        Event E;
        E.X = X[0];
        E.Y = Y[0];
        if (check(E, mid)) R = mid; else L = mid;
    }
    cout << fixed << setprecision(8) << R << endl;

    return 0;
}
