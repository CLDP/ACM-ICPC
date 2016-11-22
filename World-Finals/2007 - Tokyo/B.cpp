#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000000;


int main() {
    int times = 0;
    string P;
    while (cin >> P) {
        if (P == "end") break;
        vector<int> S;
        int N = P.size();
        for (int i = 0; i < N; ++i) {
            int a = -1, b = INF, c = P[i] - 'A';
            for (int j = 0; j < S.size(); ++j) {
                if (S[j] < c) continue;
                if (S[j] < b) {
                    b = S[j];
                    a = j;
                }
            }
            if (a != -1) {
                S[a] = c;
            } else {
                S.push_back(c);
            }
        }
        cout << "Case " << ++times << ": " << S.size() << endl;
    }
    return 0;
}
