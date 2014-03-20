#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const long double PI = acos(-1.0);
const int MAXN = 110;

int N, H[MAXN];
long double WW, HH, L[MAXN];

long double cal(long double a, long double b, long double c, long double d) {
    long double k = (b - d) / (a - c);
    if (k <= 0) return 0;
    return atan(k);
}

int print(int L) {
    int A = L / 3600;  L %= 3600;
    if (A > 9) cout << A; else cout << 0 << A;
    cout << ":";
    A = L / 60;  L %= 60;
    if (A > 9) cout << A; else cout << 0 << A;
    cout << ":";
    A = L;
    if (A > 9) cout << A; else cout << 0 << A;
    return 0;
}


int main() {
    int times = 0;
    while (cin >> N) {
        if (N == 0) break;
        
        cin >> WW >> HH;
        for (int i = 1; i < N; ++i) cin >> H[i] >> L[i];
        cin >> H[N];
        
        cout << "Apartment Complex: " << ++times << endl << endl;
        
        int Q, A, B;
        while (cin >> Q) {
            if (Q == 0) break;
            B = Q / 100, A = Q % 100;
            if (A < 1 || A > N) {
                cout << "Apartment " << Q << ": Does not exist" << endl << endl;
                continue;
            }
            if (H[A] < B || B < 1) {
                cout << "Apartment " << Q << ": Does not exist" << endl << endl;
                continue;
            }
            
            long double LD = 0, dx = 0, dy;
            for (int i = A - 1; i >= 1; --i) {
                dx += L[i];
                dy = H[i] * HH;
                long double LL = cal(dx, dy, 0, (B - 1) * HH);
                if (LL > LD) LD = LL;
                dx += WW;
            }
            int lower = 717 * 60 - 380 * 60 * (1 - LD / (PI / 2));
            cout << "Apartment " << Q << ": "; 
            print(lower);
            cout << " - ";
            
            LD = 0, dx = 0, dy = 0;
            for (int i = A + 1; i <= N; ++i) {
                dx += L[i - 1];
                dy = H[i] * HH;
                long double LL = cal(dx, dy, 0, (B - 1) * HH);
                if (LL > LD) LD = LL;
                dx += WW;
            }
            lower = 717 * 60 + 380 * 60 * (1 - LD / (PI / 2));
            print(lower);
            cout << endl << endl;
        }
    }
    return 0;
}
