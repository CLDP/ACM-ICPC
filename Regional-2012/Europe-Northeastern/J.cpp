#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt) {
        int a, b, c, p = 0;
        cin >> a >> b >> c;
        cout << 0;
        a -= 2;
        if (c % 3 < 2) {
            for (int i = 0; i < c / 3; ++i) {
                p += 3;
                cout << " " << p;
            }
            cout << " " << ++p;
            for (int i = 0; i < c / 3; ++i) {
                p -= 3;
                cout << " " << p;
            }
            cout << " " << ++p;
            for (int i = 0; i < c / 3; ++i) {
                p += 3;
                cout << " " << p;
            }
            c = c % 3;
        } else {
            for (int i = 0; i <= c / 3; ++i) {
                p += 3;
                cout << " " << p;
            }
            cout << " " << --p;
            for (int i = 0; i < c / 3; ++i) {
                p -= 3;
                cout << " " << p;
            }
            cout << " " << --p;
            for (int i = 0; i <= c / 3; ++i) {
                p += 3;
                cout << " " << p;
            }
            c = 0;
        }
        
        if (c == 1) {
            if (b >= 4) {
                cout << " " << p + 2 << " " << p + 4 << " " << p + 1 << " " << p + 3 << " " << p + 5;
                p += 5;
                b -= 4;
                while (a > 1) {
                    cout << " " << ++p;
                    --a;
                }
                for (int i = 0; i < (b + 1) / 2; ++i) {
                    p += 2;
                    cout << " " << p;
                }
                if (b % 2 == 0) ++p; else --p;
                cout << " " << p;
                for (int i = 0; i < b / 2; ++i) {
                    p -= 2;
                    cout << " " << p;
                }
            } else {
                while (a > 0) {
                    cout << " " << ++p;
                    --a;
                }
                cout << " " << p + 2 << " " << p + 4 << " " << p + 1 << " " << p + 3;
            }
        } else {
            while (a > 1) {
                cout << " " << ++p;
                --a;
            }
            for (int i = 0; i < (b + 1) / 2; ++i) {
                p += 2;
                cout << " " << p;
            }
            if (b % 2 == 0) ++p; else --p;
            cout << " " << p;
            for (int i = 0; i < b / 2; ++i) {
                p -= 2;
                cout << " " << p;
            }
        }
        cout << endl;
    }
    
    return 0;
}
