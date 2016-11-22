#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double LEN = 5 * sqrt(2.0);
const double EPS = 1e-6;

struct Point {    
    double x, y, z;    
    void set(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }
};
    
Point p[5], A, B;
int a1, a2, a3, a4;


double ZERO(double x) {
    return -EPS < x && x < EPS;
}

int getpoint(double a1, double a2, Point &A) {
    double aa = (int) a1 % 90;
    a1 = a1 / 180 * PI;
    a2 = a2 / 180 * PI;
    aa = aa / 180 * PI;
    double l = LEN / (sin(aa) + cos(aa));
    double r = l * LEN / (LEN * sin(a2) + l * cos(a2));
    A.x = r * sin(a2) * cos(a1);
    A.y = r * sin(a2) * sin(a1);
    A.z = r * cos(a2);
    return 0;
}

double sqr(double x) {
    return x * x;
}

double dis(Point a, Point b){
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
}

Point point(double ra, int x, int y) {
    Point ret;
    ret.x = (p[x].x - p[y].x) * ra + p[y].x;
    ret.y = (p[x].y - p[y].y) * ra + p[y].y;
    ret.z = (p[x].z - p[y].z) * ra + p[y].z;
    return ret;
}

double getangle(double a, double b, double c) {    
    if (ZERO(c) || ZERO(a - b - c)) return 0;    
    return acos((sqr(a) + sqr(b) - sqr(c)) / (2 * a * b));
}

double cal(int p1, int p2, Point A, Point B) {
    Point C, D;
    double ans = 1e10;
    if (a4 > 90) {
        a4 = 180 - a4;
        for (int i = 0; i < 4 ; ++i) {
            double L = 0, R = 1;
            while (R - L > 1e-4) {
                double mid1 = L + (R - L) / 3;
                C = point(mid1, i + 1, (i + 1) % 4 + 1);
                double mid2 = R - (R - L) / 3;
                D = point(mid2, i + 1, (i + 1) % 4 + 1);
                if (cal(p1, i, A, C) + cal(i, p2, C, B) > cal(p1, i, A, D) + cal(i, p2, D, B))
                    L = mid1;
                else
                    R = mid2;
            }
            ans = min(ans, cal(p1, i, A, C) + cal(i, p2, C, B));
        }
        return ans;
    }
    if (p1 == p2) return dis(A, B);
    if ((p2 + 1) % 4 == p1) {
        swap(p1, p2);
        swap(A, B);
    }
    if ((p1 + 1) % 4 == p2) {
        double a = dis(A, p[0]), b = dis(B, p[0]);
        double angle = getangle(10, a, dis(A, p[(p1 + 1) % 4 + 1])) 
                     + getangle(10, b, dis(B, p[(p1 + 1) % 4 + 1]));
        return sqrt(sqr(a) + sqr(b) - 2 * a * b * cos(angle));
    }
    double L = 0, R = 1;
    while (R - L > 1e-4) {
        double mid1 = L + (R - L) / 3;
        C = point(mid1, 0, p1 + 1);
        double mid2 = R - (R - L) / 3;
        D = point(mid2, 0, p1 + 1);
        if (dis(A, C) + cal((p1 + 3) % 4, p2, C, B) > cal((p1 + 3) % 4, p2, D, B) + dis(A, D))
            L = mid1;
        else
            R = mid2;
    }
    ans = cal((p1 + 3) % 4, p2, C, B) + dis(A, C);
    L = 0, R = 1;
    while (R - L > 1e-4) {
        double mid1 = L + (R - L) / 3;
        C = point(mid1, 0, (p1 + 1) % 4 + 1);
        double mid2 = R - (R - L) / 3;
        D = point(mid2, 0, (p1 + 1) % 4 + 1);
        if (cal((p1 + 1) % 4, p2, C, B) + dis(A, C) > cal((p1 + 1) % 4, p2, D, B) + dis(A, D))
            L = mid1;
        else
            R = mid2;
    }
    ans = min(ans, cal((p1 + 1) % 4, p2, C, B) + dis(A, C));
    return ans;
}

int main(){
    p[0].set(0, 0, LEN);
    p[1].set(LEN, 0, 0);
    p[2].set(0, LEN, 0);
    p[3].set(-LEN, 0, 0);
    p[4].set(0, -LEN, 0);
    
    int times = 0;
    while (cin >> a1 >> a2 >> a3 >> a4) {
        if (a1 == -1) break;
        if (a2 > 90 && a4 > 90) a2 = 180 - a2, a4 = 180 - a4;
        if (a2 > a4) {
            swap(a1, a3);
            swap(a2, a4);
        }
        getpoint(a1, a2, A);
        if (a4 > 90)
            getpoint(a3, 180 - a4, B);
        else
            getpoint(a3, a4, B);
        printf("Case %d: %.3lf\n", ++times, cal(a1 / 90, a3 / 90, A , B));
    }
    return 0;
}
