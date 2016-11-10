#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;
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

// Crossing angle of P0P1 -> P0P2, in (-pi, pi]
double angle(CPoint p0, CPoint &p1, CPoint p2) {
    double cr = cross(p0, p1, p2);
    double dt = dot(p0, p1, p2);
    if (dcmp(cr) == 0) cr = 0;
    if (dcmp(dt) == 0) dt = 0;
    return atan2(cr, dt);
}
// p0 on p1p2
int PointOnLine(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0;
}
int PointOnSegment(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0 && dcmp(dot(p0, p1, p2)) <= 0;
}
// 1 -> cross,   0 -> parallel,  -1 -> overlap
int LineIntersection(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint &cp) {
    double u = cross(p1, p2, p3), v = cross(p2, p1, p4);
    if (dcmp(u + v)) {
        cp.x = (p3.x * v + p4.x * u) / (u + v);
        cp.y = (p3.y * v + p4.y * u) / (u + v);
        return 1;
    }
    if (dcmp(u)) return 0;
    if (dcmp(cross(p3, p4, p1))) return 0;
    return -1;
}
// 1 ->intersect, 0 -> not (include parallel), -1 -> parallel and overlap
int SegmentIntersection(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint &cp) {
    int ret = LineIntersection(p1, p2, p3, p4, cp);
    if (ret == 1) return dcmp(dot(cp, p1, p2)) <= 0 && dcmp(dot(cp, p3, p4)) <= 0;
    if (ret == -1 && (PointOnSegment(p1, p3, p4) || PointOnSegment(p2, p3, p4) 
                   || PointOnSegment(p3, p1, p2) || PointOnSegment(p4, p1, p2))) return -1;
    return 0;
}

CPoint X[7];

int printP(CPoint C) {
    cout << C.x << " " << C.y << endl;
    return 0;
}

bool check(vector<int> H) {
    H.push_back(H[0]);
    CPoint trash;
    for (int i = 0; i < 7; ++i) 
     for (int j = i + 2; j < 7; ++j) {
         if (i == 0 && j == 6) continue;
         if (SegmentIntersection(X[H[i]], X[H[i + 1]], X[H[j]], X[H[j + 1]], trash)) {
         /*
             printP(X[H[i]]);
             printP(X[H[i + 1]]);
             printP(X[H[j]]);
             printP(X[H[j + 1]]);
             cout << i << " " << j << " " << SegmentIntersection(X[H[i]], X[H[i] + 1], X[H[j]], X[H[j + 1]], trash) << endl;
             printP(trash);
             */
             return false;
         }
     }
    return true;
}

double areaf(vector<int> &H) {
   CPoint P;
   P.x = X[H[1]].x - X[H[0]].x;
   P.y = X[H[1]].y - X[H[0]].y;
   double ans = 0;
   for (int i = 2; i < 7; ++i) {
       CPoint Q;
       Q.x = X[H[i]].x - X[H[0]].x;
       Q.y = X[H[i]].y - X[H[0]].y;
       ans = ans + (P.x * Q.y - P.y * Q.x) / 2;
       P = Q;
   }
   return fabs(ans);
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        for (int i = 0; i < 7; ++i) scanf("%lf%lf", &X[i].x, &X[i].y);
        double res;
        scanf("%lf", &res);
        vector<int> H;
        vector<int> ans;
        for (int i = 0; i < 7; ++i) H.push_back(i);
        while (true) {
            if (H[0] != 0) break;
            if (check(H)) {
                double area = areaf(H) / 4;
                area = area * area * area;
                if (fabs(area - res) < 1e-5) {
                    if (ans.empty() || H < ans) ans = H;
                }
            }
            next_permutation(H.begin(), H.end());
        }
        for (int i = 0; i < 7; ++i) {
            cout << ans[i] + 1;
            if (i != 6) cout << " "; else cout << endl;
        }
    }
    
    return 0;
}
