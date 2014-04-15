#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const double EPS = 1e-8;
const double PI = acos(-1.0);

struct Point {
    double x, y, z;
};


double sqr(double x) { return x * x; }

int dcmp(double x) {
    if (x < -EPS) return -1; else return (x > EPS);
}

Point operator + (Point p1, Point p2) {
    Point P;
    P.x = p1.x + p2.x;
    P.y = p1.y + p2.y;
    P.z = p1.z + p2.z;
    return P;
}

Point operator - (Point p1, Point p2) {
    Point P;
    P.x = p1.x - p2.x;
    P.y = p1.y - p2.y;
    P.z = p1.z - p2.z;
    return P;
}

Point operator * (Point p1, double D) {
    Point P;
    P.x = p1.x * D;
    P.y = p1.y * D;
    P.z = p1.z * D;
    return P;
}

Point operator / (Point p1, double D) {
    Point P;
    P.x = p1.x / D;
    P.y = p1.y / D;
    P.z = p1.z / D;
    return P;
}

Point operator ^ (Point p0, Point p1) {
    Point Q;
    Q.x = p0.y * p1.z - p1.y * p0.z;
    Q.y = p0.z * p1.x - p1.z * p0.x;
    Q.z = p0.x * p1.y - p1.x * p0.y;
    return Q;
}

double operator * (Point p0, Point p1) {
    return p0.x * p1.x + p0.y * p1.y + p0.z * p1.z;
}

double abs(Point A) {
    return sqrt(A * A);
}

double dissqr(Point p1, Point p2) {
    return sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z);
}

double dis(Point p1, Point p2) {
    return sqrt(dissqr(p1, p2));
}

bool PointEqual(const Point &p1, const Point &p2) {
    return dcmp(p1.x - p2.x) == 0 && dcmp(p1.y - p2.y) == 0 && dcmp(p1.z - p2.z) == 0;
}

double Volume(Point A, Point B, Point C, Point D) {
    return fabs(((B - A) ^ (C - A)) * (D - A)) / 6;
}


Point P[6], G;
vector<Point> Q;


int FindCenter() {
    double V1 = Volume(P[0], P[1], P[2], P[3]);
    double V2 = Volume(P[0], P[1], P[2], P[4]);
    Point G1 = (P[0] + P[1] + P[2] + P[3]) / 4;
    Point G2 = (P[0] + P[1] + P[2] + P[4]) / 4;
    G = G1 + (G2 - G1) * V2 / (V1 + V2);
    return 0;
}

bool allsameside(Point A, Point B, Point C) {
    Point Nor = (B - A) ^ (C - A);
    bool plus = false, minus = false;
    for (int i = 0; i < 5; ++i) {
        if (PointEqual(A, P[i]) || PointEqual(B, P[i]) || PointEqual(C, P[i])) continue;
        double temp = (P[i] - A) * Nor;
        if (dcmp(temp) == -1) minus = true; 
        if (dcmp(temp) == 1) plus = true;
    }
    if (plus && minus) return false;
    Q.clear();
    for (int i = 0; i < 5; ++i) {
        double temp = (P[i] - A) * Nor;
        if (dcmp(temp) == 0) Q.push_back(P[i]);
    }
    return true;
}

Point Shadow(Point P, Point A, Point B, Point C) {
    Point Nor = (B - A) ^ (C - A);
    Point Nor0 = Nor * (Nor * (P - A)) / abs(Nor) / abs(Nor);
    return P - Nor0;
}

double ShadowHeight(Point P, Point A, Point B, Point C) {
    Point Nor = (B - A) ^ (C - A);
    return fabs(Nor * (P - A) / abs(Nor));
}

bool SameSide(Point A, Point B, Point P, Point Q) {
    Point v1 = (B - A) ^ (P - A);
    Point v2 = (B - A) ^ (Q - A);
    return v1 * v2 >= 0;
}

bool PointInTriangle(Point A, Point B, Point C, Point P) {
    return SameSide(A, B, C, P) && SameSide(B, C, A, P) && SameSide(C, A, B, P);
}

bool PointInArea(Point P) {
    for (int i = 0; i < Q.size(); ++i)
     for (int j = i + 1; j < Q.size(); ++j)
      for (int k = j + 1; k < Q.size(); ++k)
       if (PointInTriangle(Q[i], Q[j], Q[k], P)) return true;
    return false;
}

double DistanceToLine(Point A, Point B, Point P) {
    if (dcmp((B - A) * (P - A)) == 1 && dcmp((A - B) * (P - B)) == 1) 
        return sqrt(dissqr(A, P) - sqr((B - A) * (P - A) / abs(B - A)));
    return min(dis(A, P), dis(B, P));
}

bool Balance(Point P) {
    if (!PointInArea(P)) return false;
    for (int i = 0; i < Q.size(); ++i)
     for (int j = i + 1; j < Q.size(); ++j) {
         int k1, k2;
         for (k1 = 0; k1 < Q.size(); ++k1) {
             if (k1 == i || k1 == j) continue;
             break;
         }
         for (k2 = k1 + 1; k2 < Q.size(); ++k2) {
             if (k2 == i || k2 == j) continue;
             break;
         }
         if (k2 != Q.size() && !SameSide(Q[i], Q[j], Q[k1], Q[k2])) continue;
         if (DistanceToLine(Q[i], Q[j], P) < 0.2) return false;
     }
    return true;
}

int main() {
    int times = 0;
    while (cin >> P[0].x >> P[0].y >> P[0].z) {
        for (int i = 1; i < 6; ++i) cin >> P[i].x >> P[i].y >> P[i].z;
        FindCenter();
        double ansMin = 1e10, ansMax = 0;
        
        for (int i = 0; i < 5; ++i)
         for (int j = i + 1; j < 5; ++j)
          for (int k = j + 1; k < 5; ++k) {
              if (!allsameside(P[i], P[j], P[k])) continue;
              Point G0 = Shadow(G, P[i], P[j], P[k]);
              if (Balance(G0)) {
                  ansMin = min(ansMin, ShadowHeight(P[5], P[i], P[j], P[k]));
                  ansMax = max(ansMax, ShadowHeight(P[5], P[i], P[j], P[k]));
              }
          }
        
        printf("Case %d: %.5lf %.5lf\n", ++times, ansMin, ansMax);
    }
    return 0;
}
