#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const double strange = 1.1827364823;
const int INF = 1000000000;
const double PI = 3.14159265358979323846;


struct point {
    double x, y, z;
};

point A[6];

int line(double &a, double &b, double &x1, double &y1, double &p1, 
    double &x2, double &y2, double &p2) {
    b = (p1 * x2 - p2 * x1) / (y1 * x2 - y2 * x1);
    a = (p1 - b * y1) / x1;
    // what if zero??
    return 0;
}


int plane(double &a, double &b, double &c, point A, point B, point C) {
    double x1 = A.y * B.x - B.y * A.x;
    double y1 = A.z * B.x - B.z * A.x;
    double z1 = A.x - B.x;
    double x2 = B.y * C.x - C.y * B.x;
    double y2 = B.z * C.x - B.x * C.z;
    double z2 = B.x - C.x;
    line(b, c, x1, y1, z1, x2, y2, z2);
    a = (-1 - c * A.z - b * A.y) / A.x;
    // what if zero??
    return 0;
}

double getP(double a, double b, double c, point A) {
    return a * A.x + b * A.y + c * A.z + 1;
}

int swap(point &A, point &B) {
    swap(A.x, B.x);
    swap(A.y, B.y);
    swap(A.z, B.z);
    return 0;
}

point seg_plane(double a, double b, double c, point B, point C) {
    double t1 = getP(a, b, c, B);
    double t2 = getP(a, b, c, C);
    point mid;
    for (int i = 0; i < 100; ++i) {
        mid.x = (B.x + C.x) / 2;
        mid.y = (B.y + C.y) / 2;
        mid.z = (B.z + C.z) / 2;
        
        double t3 = getP(a, b, c, mid);
        if (t3 == 0) return mid;
        if (t3 > 0) {
            if (t1 > 0) {
                B = mid;
            } else {
                C = mid;
            }
        } else {
            if (t1 < 0) {
                B = mid;
            } else {
                C = mid;
            }
        }
    }
    return mid;
}

bool inside(double a, double b, double c, point AA) {
    double a1, b1, c1, t1, t2;
    // Same side as A[2];
    point tt = A[2];
    tt.x += 1;
    plane(a1, b1, c1, A[0], A[1], tt);
    t1 = getP(a1, b1, c1, A[2]);
    t2 = getP(a1, b1, c1, AA);
    if (t1 > 0 && t2 < 0) return false;
    if (t1 < 0 && t2 > 0) return false;
    
    // Same side as A[1]
    tt = A[1];
    tt.x += 1;
    plane(a1, b1, c1, A[0], A[2], tt);
    t1 = getP(a1, b1, c1, A[1]);
    t2 = getP(a1, b1, c1, AA);
    if (t1 > 0 && t2 < 0) return false;
    if (t1 < 0 && t2 > 0) return false;
    
    // Same side as A[0]
    tt = A[0];
    tt.x += 1;
    plane(a1, b1, c1, A[1], A[2], tt);
    t1 = getP(a1, b1, c1, A[0]);
    t2 = getP(a1, b1, c1, AA);
    if (t1 > 0 && t2 < 0) return false;
    if (t1 < 0 && t2 > 0) return false;
    
    return true;
}


bool checkI(double a, double b, double c, point A, point B, point C) {
    // A is in the plane
    point P1 = seg_plane(a, b, c, B, C);
    bool if_in1 = inside(a, b, c, A);
    bool if_in2 = inside(a, b, c, P1);
    if (if_in1 != if_in2)
        return true;
    else
        return false;
}

bool check(double a, double b, double c, point A, point B, point C) {
    // A is on different side with B, C
    point P1 = seg_plane(a, b, c, A, B);
    point P2 = seg_plane(a, b, c, A, C);
    bool if_in1 = inside(a, b, c, P1);
    bool if_in2 = inside(a, b, c, P2);
    if (if_in1 != if_in2)
        return true;
    else
        return false;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> A[j].x >> A[j].y >> A[j].z;
            A[j].x += strange;
            A[j].y += strange + 1e-8;
            A[j].z += strange - 1e-8;
        }
        double a, b, c;
        plane(a, b, c, A[0], A[1], A[2]);
        double g3 = getP(a, b, c, A[3]);
        double g4 = getP(a, b, c, A[4]);
        double g5 = getP(a, b, c, A[5]);
        if (g5 > g4) {
            swap(g5, g4);
            swap(A[5], A[4]);
        }
        if (g4 > g3) {
            swap(g4, g3);
            swap(A[4], A[3]);
        }
        if (g5 > g4) {
            swap(g5, g4);
            swap(A[5], A[4]);
        }
        
        if (g3 > 0) {
            if (g4 > 0) {
                if (g5 >= 0) {
                    // 1 1 1, 1 1 0
                    cout << "NO" << endl;
                } else {
                    // 1 1 -1
                    if (check(a, b, c, A[5], A[3], A[4]))
                        cout << "YES" << endl;
                    else
                        cout << "NO" << endl;
                }
            } else
            if (g4 == 0) {
                if (g5 == 0) {
                    // 1 0 0
                    cout << "NO" << endl;
                } else {
                    // 1 0 -1
                    if (checkI(a, b, c, A[4], A[3], A[5]))
                        cout << "YES" << endl;
                    else
                        cout << "NO" << endl;
                }
            } else {
                // 1 -1 -1
                if (check(a, b, c, A[3], A[4], A[5]))
                    cout << "YES" << endl;
                else
                    cout << "NO" << endl;
            }
        } else
        if (g3 == 0) {
            if (g4 == 0) {
                // 0 0 ?
                cout << "NO" << endl;
            } else {
                // 0 -1 -1
                cout << "NO" << endl;
            }
        } else {
            // -1 -1 -1
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
