#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

double dist(double A, double B, double C, double D) {
    return sqrt((A - C) * (A - C) + (B - D) * (B - D));
}

double cal(string P, string Q) {
    double X = 0;
    X = (P[0] - '0') * 10 + (P[1] - '0') - 9;
    X = X * 60 + (P[3] - '0') * 10 + (P[4] - '0');
    
    double Y = 0;
    Y = (Q[0] - '0') * 10 + (Q[1] - '0');
    Y = Y * 60 + (Q[3] - '0') * 10 + (Q[4] - '0');
    
    return X + Y;
}

int main() {
    double xa, ya, xb, yb, xc, yc;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;
    double D, V;
    cin >> D >> V;
    V /= 60;
    string P, Q;
    cin >> P >> Q;
    double S;
    cin >> S;
    S /= 60;
    double T1 = dist(xa, ya, xc, yc) / V + D + dist(xb, yb, xc, yc) / V;
    double T2 = cal(P, Q);
    double T3 = dist(xa, ya, xb, yb) / S;
    if (fabs((yc - ya) * (xa - xb) - (xc - xa) * (ya - yb)) < 1e-6) T3 += D; 
    
    if (T1 < T2 && T1 < T3) {
        cout << "Alex" << endl;
        return 0;
    }
    if (T2 < T1 && T2 < T3) {
        cout << "Dmitry" << endl;
        return 0;
    }
    cout << "Petr" << endl;
    
    return 0;
}
