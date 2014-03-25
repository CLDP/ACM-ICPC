#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-6;

struct circle {
    double a, b, r;
};


double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


int solve(double &x1, double &x2, int &num, double A, double B, double C) {
    double delta = B * B - 4 * A * C;
    if (delta < 0) {
        num = 0;
        return 0;
    }
    if (fabs(delta) < EPS) {
        x1 = x2 = - B / (2 * A);
        num = 1;
    } else {
        x1 = (- B + sqrt(delta)) / (2 * A);
        x2 = (- B - sqrt(delta)) / (2 * A);
        num = 2;
    }
    return 0;
}


int get(double &x1, double &y1, double &x2, double &y2, int &num, circle C1, circle C2) {
    double A = 2 * (C2.a - C1.a);
    double B = 2 * (C2.b - C1.b);
    double C = C1.a * C1.a - C2.a * C2.a + C1.b * C1.b - C2.b * C2.b - C1.r * C1.r + C2.r * C2.r;
    
    if (fabs(A) < EPS) {
        y1 = y2 = -C / B;
        solve(x1, x2, num, 1, -2 * C1.a, C1.a * C1.a + (- y1 - C1.b) * (- y1 - C1.b) - C1.r * C1.r);
    } else {
        solve(y1, y2, num, 1 + (B / A) * (B / A), 2 * ((C / A + C1.a) * B / A - C1.b), 
             (C / A + C1.a) * (C / A + C1.a) + C1.b * C1.b - C1.r * C1.r);
        x1 = - B / A * y1 - C / A;
        x2 = - B / A * y2 - C / A;
    }
    return 0;
}


int main() {
    int N, times = 0;
    double T, A, B;
    while (cin >> N >> T >> A >> B) {
        if (N == 0) break;
        vector<circle> X;
        for (int i = 0; i < N; ++i) {
            double XX, YY, D, TT;
            cin >> XX >> YY >> D >> TT;
            D = 90 - D;
            XX += cos(D / 180 * PI) * TT * 100;
            YY += sin(D / 180 * PI) * TT * 100;
            circle C;
            C.a = XX, C.b = YY;
            C.r = (T - TT) * 350;
            X.push_back(C);
        }
        
        int flag = -1;
        double P, Q;
        if (N == 1) {
            if (X[0].r <= 0.05) {
                P = X[0].a;
                Q = X[0].b;
                flag = 1;
            } else {
                flag = 100;
            }
        } else {
            double x1, y1, x2, y2;
            get(x1, y1, x2, y2, flag, X[0], X[1]);
            if (flag > 0) {
                bool F1 = true, F2 = true;
                for (int i = 2; i < N; ++i) {
                    if (fabs(dist(x1, y1, X[i].a, X[i].b) - X[i].r) > 0.1) F1 = false;
                    if (fabs(dist(x2, y2, X[i].a, X[i].b) - X[i].r) > 0.1) F2 = false;
                }
                if (flag == 2) {
                    flag = F1 + F2;
                    if (flag == 1) {
                        if (F1) P = x1, Q = y1; else P = x2, Q = y2;
                    } else 
                    if (flag == 2) {
                        if (dist(x1, y1, x2, y2) < 0.1) {
                            flag = 1;
                            P = x1, Q = y1;
                        }
                    }
                } else {
                    P = x1, Q = y1;
                }
            }
        }
        
        cout << "Trial " << ++times << ": ";
        if (flag > 1) {
            cout << "Inconclusive" << endl;
        } else 
        if (flag == 1) {
            if (dist(P, Q, A, B) < 0.1) {
                cout << "Arrived" << endl;
            } else {
                double degree = 90 - 180 * atan2(B - Q, A - P) / PI;
                if (degree < 0) degree += 360;
                if (degree >= 360) degree -= 360;
                cout << round(degree) << " degrees" << endl;
            }
        } else {
            cout << "Inconsistent" << endl;
        }
    }
    return 0;
}
