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

long long W[30], P[30];

int main() {
    W[0] = P[0] = 1;
    for (int i = 1; i < 30; ++i) {
        W[i] = W[i - 1] * 3;
        P[i] = 3 * P[i - 1] + 2 * W[i - 1];
        if (W[i] > 10000000) break;
    }
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int M;
        cin >> M;
        vector<int> X;
        while (M > 0) {
            X.push_back(M % 3);
            M /= 3;
        }
        for (int i = X.size() - 1; i > 0; --i) {
            cout << X[i] << " ";
        }
        cout << X[0] << endl;
    }
    return 0;
}
