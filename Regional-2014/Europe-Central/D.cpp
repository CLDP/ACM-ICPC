#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const string CL = "clockwise";
const string CCL = "counterclockwise";

int x[1010], y[1010], d[1010];
vector<int> X[1010];
long long a[1010], b[1010];
bool c[1010];

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    int times;
    cin >> times;
    while (times--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> x[i] >> y[i] >> d[i];
            X[i].clear();
        }
        for (int i = 0; i < N; ++i) 
         for (int j = i + 1; j < N; ++j) {
             if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) == (d[i] + d[j]) * (d[i] + d[j])) {
                 X[i].push_back(j);
                 X[j].push_back(i);
             }
         }
        
        memset(b, 0, sizeof(b));
        a[0] = b[0] = c[0] = 1;
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int t = Q.front();
            Q.pop();
            for (int i = 0; i < X[t].size(); ++i) {
                int p = X[t][i];
                if (b[p] != 0) continue;
                a[p] = a[t] * d[t];
                b[p] = b[t] * d[p];
                long long GG = gcd(a[p], b[p]);
                a[p] /= GG;
                b[p] /= GG;
                c[p] = !c[t];
                Q.push(p);
            }
        }
        
        for (int i = 0; i < N; ++i) {
            if (b[i] == 0) {
                cout << "not moving" << endl;
                continue;
            }
            if (b[i] == 1) cout << a[i] << " "; else cout << a[i] << "/" << b[i] << " ";
            if (c[i]) cout << CL << endl; else cout << CCL << endl;
        }
    }
    return 0;
}
