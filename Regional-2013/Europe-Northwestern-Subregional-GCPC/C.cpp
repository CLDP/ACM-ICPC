#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;
const double PI = 3.14159265358979323846;



int main() {
    int i, j, a, b, c, d, n;
    
    cin >> n;
    while (n--) {
        char x, y;
        vector<int> a1, b1;
        cin >> x >> b >> y >> d;
        
        a = (int)(x - 'A') + 1;
        c = (int)(y - 'A') + 1;
        if (((a + b) % 2) != ((c + d) % 2))
            cout << "Impossible\n";
        else {
            a1.push_back(a);
            b1.push_back(b);
            if ((a + b) % 2 == 0) {
                if (a != b) {
                    a1.push_back((a + b) / 2);
                    b1.push_back((a + b) / 2);
                }
                if (a + b != c + d) {
                    a1.push_back((c + d) / 2);
                    b1.push_back((c + d) / 2);
                }
                if (c != d) {
                    a1.push_back(c);
                    b1.push_back(d);
                }
            } else {
                if (a + b != 9) {
                    i = (a + b - 9) / 2;
                    a1.push_back(a - i);
                    b1.push_back(b - i);
                    a = a - i;
                    b = b - i;
                }
                if (a - b != c - d) {
                    j = (c + d - 9) / 2;
                    a1.push_back(c - j);
                    b1.push_back(d - j);
                }
                if (c + d != 9) {
                    a1.push_back(c);
                    b1.push_back(d);
                }
            }
            cout << a1.size() - 1;
            for (i = 0; i < a1.size(); ++i)
                cout << " " << (char)('A' + a1[i] - 1) << " " << b1[i];
            cout << endl;
        }
    }
    
    return 0;
}
