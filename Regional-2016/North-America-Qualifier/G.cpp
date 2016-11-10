#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF1 = 1000000007;
const int INF2 = 100000007;

int main() {
    long long A = 0, B = 0;
    string P;
    getline(cin, P);
    for (int i = 0; i < P.size(); ++i) {
        long long c = P[i] - '0';
        A = (A * 10 + c) % INF1;
        B = (B * 10 + c) % INF2;
    }
    
    long long C = 1, D = 1;
    for (int i = 1; i < 1000001; ++i) {
        C = (C * i) % INF1;
        D = (D * i) % INF2;
        if (C == A && D == B) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
