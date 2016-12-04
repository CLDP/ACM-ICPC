#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const double PI = acos(-1.0);
const double INF = 1e100;
const double EPS = 1e-8;

struct Point {
    double x, y;
};

struct center {
    Point X;
    double weight;
};

Point X[MAXN];
vector<center> Y;

Point Center(Point A, Point B, Point C) {
    Point T;
    T.x = (A.x + B.x + C.x) / 3;
    T.y = (A.y + B.y + C.y) / 3;
    return T;
}

double cross(Point S, Point A, Point B) {
    double x1 = A.x - S.x, y1 = A.y - S.y;
    double x2 = B.x - S.x, y2 = B.y - S.y;
    return x1 * y2 - x2 * y1;
}


int main() {
    int N;
    cin >> N;
    double LL = 10000, RR = -10000;
    for (int i = 0; i < N; ++i) {
        cin >> X[i].x >> X[i].y;
        if (X[i].y == 0) {
            LL = min(X[i].x, LL);
            RR = max(X[i].x, RR);
        }
    }
    double S = 0, total_weight = 0;
    for (int i = 1; i + 1 < N; ++i) {
        S += cross(X[0], X[i + 1], X[i]);
        center T;
        T.X = Center(X[0], X[i + 1], X[i]);
        T.weight = cross(X[0], X[i + 1], X[i]);
        total_weight += T.weight;
        Y.push_back(T);
    }
    
    Point TT;
    TT.x = TT.y = 0;
    for (int i = 0; i < Y.size(); ++i) {
        TT.x += Y[i].weight * Y[i].X.x;
        TT.y += Y[i].weight * Y[i].X.y;
    }

    TT.x /= total_weight;
    TT.y /= total_weight;
    total_weight = fabs(total_weight) / 2;

    double A = total_weight * (TT.x - LL) / (LL - X[0].x);
    double B = total_weight * (TT.x - RR) / (RR - X[0].x);

    if (fabs(LL - X[0].x) < EPS || fabs(RR - X[0].x) < EPS) {
        if (LL - EPS <= TT.x && TT.x <= RR + EPS) {
            cout << "0 .. inf" << endl;
            return 0;
        } else 
        if (fabs(LL - X[0].x) < EPS && TT.x < LL - EPS) {
            cout << "unstable" << endl;
            return 0;
        } else
        if (fabs(RR - X[0].x) < EPS && TT.x > RR + EPS) {
            cout << "unstable" << endl;
            return 0;
        }
    }

    if (TT.x < LL - EPS) {
        if (X[0].x < LL) {
            cout << "unstable" << endl;
        } else
        if (X[0].x > RR) {
            cout << (int)floor(A + EPS) << " .. " << (int)ceil(B - EPS) << endl;
        } else {
            cout << (int)floor(A + EPS) << " .. inf" << endl;
        }
    } else 
    if (TT.x > RR + EPS) {
        if (X[0].x < LL) {
            cout << (int)floor(B + EPS) << " .. " << (int)ceil(A - EPS) << endl;
        } else
        if (X[0].x > RR) {
            cout << "unstable" << endl;
        } else {
            cout << (int)floor(B + EPS) << " .. inf" << endl;
        }
    } else {
        if (X[0].x < LL) {
            cout << "0 .. " << (int)ceil(A - EPS) << endl;
        } else
        if (X[0].x > RR) {
            cout << "0 .. " << (int)ceil(B - EPS) << endl;
        } else {
            cout << "0 .. inf" << endl;
        }
    }

    return 0;
}
