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


int n;
int x[10000];
int y[10000];
int a[1000][1000];
int test;

int check(int i, int j){
    return abs(x[i] - x[j]) + abs(y[i] - y[j]) <= 1000;
}

int main() {
    cin >> test;
    for(int T = 0; T < test; ++T) {
        cin >> n;
        for (int i = 0; i < n + 2; ++i) cin >> x[i] >> y[i];
        for (int i = 0; i < n + 2; ++i)
            for (int j = 0; j < n + 2; ++j)
                if (check(i, j)) a[i][j] = 1; else a[i][j] = 0; 

        for (int k = 0; k < n + 2; ++k)
            for (int i = 0; i < n + 2; ++i)
                for (int j = 0; j < n + 2; ++j)
                    if (a[i][k] && a[k][j]) a[i][j] = 1;

        if (a[0][n + 1]) cout << "happy" << endl; else cout << "sad" << endl;
    }
    
    return 0;
}
