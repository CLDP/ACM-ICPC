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

int x[110][110];

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int A, B, C;
        cin >> C >> A >> B;
        --A;
        --B;
        x[A][B] = C;
    }
    int ans = 0;
    cin >> M;
    for (int t = 0; t < M; ++t) {
        string P;
        int A, B, C;
        cin >> P >> C >> A >> B;
        --A;
        --B;
        if (P == "L") {
            for (int i = 0; i < N; ++i) {
                vector<int> Q;
                for (int j = 0; j < N; ++j) 
                 if (x[i][j] > 0) {
                     Q.push_back(x[i][j]);
                     x[i][j] = 0;
                 }
                int k = 0;
                for (int j = 0; j < Q.size(); ++j) {
                    if (j < Q.size() - 1 && Q[j] == Q[j + 1]) {
                        x[i][k] = Q[j] + Q[j];
                        ans += Q[j] + Q[j];
                        ++j;
                    } else {
                        x[i][k] = Q[j];
                    }
                    ++k;
                }
            }
        } else
        if (P == "R") {
            for (int i = 0; i < N; ++i) {
                vector<int> Q;
                for (int j = N - 1; j >= 0; --j) 
                 if (x[i][j] > 0) {
                     Q.push_back(x[i][j]);
                     x[i][j] = 0;
                 }
                int k = N - 1;
                for (int j = 0; j < Q.size(); ++j) {
                    if (j < Q.size() - 1 && Q[j] == Q[j + 1]) {
                        x[i][k] = Q[j] + Q[j];
                        ans += Q[j] + Q[j];
                        ++j;
                    } else {
                        x[i][k] = Q[j];
                    }
                    --k;
                }
            }
        } else
        if (P == "U") {
            for (int i = 0; i < N; ++i) {
                vector<int> Q;
                for (int j = 0; j < N; ++j) 
                 if (x[j][i] > 0) {
                     Q.push_back(x[j][i]);
                     x[j][i] = 0;
                 }
                int k = 0;
                for (int j = 0; j < Q.size(); ++j) {
                    if (j < Q.size() - 1 && Q[j] == Q[j + 1]) {
                        x[k][i] = Q[j] + Q[j];
                        ans += Q[j] + Q[j];
                        ++j;
                    } else {
                        x[k][i] = Q[j];
                    }
                    ++k;
                }
            }
        } else {
            for (int i = 0; i < N; ++i) {
                vector<int> Q;
                for (int j = N - 1; j >= 0; --j) 
                 if (x[j][i] > 0) {
                     Q.push_back(x[j][i]);
                     x[j][i] = 0;
                 }
                int k = N - 1;
                for (int j = 0; j < Q.size(); ++j) {
                    if (j < Q.size() - 1 && Q[j] == Q[j + 1]) {
                        x[k][i] = Q[j] + Q[j];
                        ans += Q[j] + Q[j];
                        ++j;
                    } else {
                        x[k][i] = Q[j];
                    }
                    --k;
                }
            }
        }
        x[A][B] = C;
    }
    
    cout << ans << endl;
    
    return 0;
}
