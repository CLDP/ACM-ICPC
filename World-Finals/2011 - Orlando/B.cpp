#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int C[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

struct point {
    int x, y;
};

struct seg {
    point A[3];
};

bool sameP(const point &A, const point &B) {
    return A.x == B.x && A.y == B.y;
}

bool sameS(const seg &A, const seg &B) {
    for (int i = 0; i < 3; ++i) {
        if (!sameP(A.A[i], B.A[i])) return false; 
    }
    return true;
}

int gcd(int a, int b) {
    a = abs(a), b = abs(b);
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

point rotate(point A, double theta) {
    if (A.x == 0 && A.y == 0) return A;
    double alpha = atan2(A.y, A.x), R = sqrt(A.x * A.x + A.y * A.y);
    point B;
    B.x = round(R * cos(alpha + theta)), B.y = round(R * sin(alpha + theta));
    return B;
}

int printP(const point &A) {
    cout << "(" << A.x << " " << A.y << ")" << endl;
    return 0;
}

int printS(const seg &A) {
    for (int i = 0; i < 3; ++i)
        cout << "(" << A.A[i].x << " " << A.A[i].y << ")" << " ";
    cout << endl;
    return 0;
}


int main() {
    int times = 0;
    seg ORI, FIN;
    while (cin >> ORI.A[0].x >> ORI.A[0].y >> ORI.A[1].x >> ORI.A[1].y >> ORI.A[2].x >> ORI.A[2].y) {
        if (ORI.A[0].x == 0 && ORI.A[0].y == 0 && ORI.A[1].x == 0 && ORI.A[1].y == 0) break;
        for (int i = 0; i < 3; ++i) cin >> FIN.A[i].x >> FIN.A[i].y;
        
        int ans = 0;
        point D, E;
        D.x = 783, D.y = 823;
        
        for (int x = -10; x <= 10; ++x)
         for (int y = -10; y <= 10; ++y) {
             if (x != 10 && x != -10 && y != 10 && y != -10) continue;
             double theta = atan2(1.0 * y, 1.0 * x);
             seg T1;
             for (int i = 0; i < 3; ++i) T1.A[i] = rotate(ORI.A[i], theta);
             point D1 = rotate(D, theta);
             
             for (int i = 0; i < 6; ++i) {
                 bool flag = true;
                 int dx = 0, dy = 0;
                 seg T2;
                 for (int j = 0; j < 3; ++j) T2.A[j] = T1.A[C[i][j]];
                 
                 for (int j = 0; j < 2; ++j) {
                     if (T2.A[j].x == T2.A[j + 1].x || FIN.A[j].x == FIN.A[j + 1].x) {
                         if (FIN.A[j].x != FIN.A[j + 1].x) flag = false;
                         continue;
                     }
                     if ((FIN.A[j].x - FIN.A[j + 1].x) % (T2.A[j].x - T2.A[j + 1].x) != 0) flag = false;
                     int temp = (FIN.A[j].x - FIN.A[j + 1].x) / (T2.A[j].x - T2.A[j + 1].x);
                     if (dx == 0 || dx == temp) {
                         dx = temp;
                     } else {
                         flag = false;
                     }
                 }
                 if (!flag) continue;
                 
                 for (int j = 0; j < 2; ++j) {
                     if (T2.A[j].y == T2.A[j + 1].y || FIN.A[j].y == FIN.A[j + 1].y) {
                         if (FIN.A[j].y != FIN.A[j + 1].y) flag = false;
                         continue;
                     }
                     if ((FIN.A[j].y - FIN.A[j + 1].y) % (T2.A[j].y - T2.A[j + 1].y) != 0) flag = false;
                     int temp = (FIN.A[j].y - FIN.A[j + 1].y) / (T2.A[j].y - T2.A[j + 1].y);
                     if (dy == 0 || dy == temp) {
                         dy = temp;
                     } else {
                         flag = false;
                     }
                 }
                 if (!flag) continue;
                 
                 if (dx == 0) dx = 1;
                 if (dy == 0) dy = 1;
                 
                 seg T3;
                 for (int j = 0; j < 3; ++j) {
                     T3.A[j].x = T2.A[j].x * dx;
                     T3.A[j].y = T2.A[j].y * dy;
                 }
                      
                 point D3;
                 D3.x = D1.x * dx, D3.y = D1.y * dy;
                      
                 flag = true;
                 int mx = FIN.A[0].x - T3.A[0].x, my = FIN.A[0].y - T3.A[0].y;
                 for (int j = 1; j < 3; ++j) {
                     int mxx = FIN.A[j].x - T3.A[j].x;
                     int myy = FIN.A[j].y - T3.A[j].y;
                     if (mxx != mx || myy != my) flag = false;
                 }
                 
                 D3.x += mx, D3.y += my;
                      
                 if (flag) {
                     if (ans == 0) {
                         ++ans;
                         E = D3;
                     } else {
                         if (ans == -1) break;
                         if (!sameP(E, D3)) {
                             ans = -1;
                             break;
                         } else {
                             ++ans;
                         }
                     }
                 }  
                   
                 flag = true;
                 if (FIN.A[0].x % dx != 0 || FIN.A[0].y % dy != 0) flag = false;
                 if (!flag) continue;
                 
                 mx = FIN.A[0].x / dx - T3.A[0].x, my = FIN.A[0].y / dy - T3.A[0].y;
                      
                 for (int i = 1; i < 3; ++i) {
                     int mxx = FIN.A[i].x / dx - T3.A[i].x;
                     int myy = FIN.A[i].y / dy - T3.A[i].y;
                     if (mx != mxx || my != myy) flag = false;
                 }
                 
                 if (flag) {
                     for (int j = 0; j < 3; ++j) {
                         T3.A[j].x = (T2.A[j].x + mx) * dx;
                         T3.A[j].y = (T2.A[j].y + my) * dy;
                         if (!sameS(T3, FIN)) continue;
                               
                         D3.x = (D1.x + mx) * dx;
                         D3.y = (D1.y + my) * dy;
                         if (ans == 0) {
                             ++ans;
                             E = D3;
                         } else {
                             if (ans == -1) break;
                             if (!sameP(E, D3)) {
                                 ans = -1;
                                 break;
                             } else {
                                 ++ans;
                             }
                         }
                     }
                 }
             }
         }
         cout << "Case " << ++times << ": ";
         switch (ans) {
             case 0 : cout << "no solution" << endl; break;
             case -1: cout << "inconsistent solutions" << endl; break;
             default: cout << "equivalent solutions" << endl; break;
         }
    }
    return 0;
}
