#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[110][110];
pair<int, int> y[11];


int main() {
    int N, M, C;
    cin >> N >> M >> C;
    for (int i = 1; i <= C; ++i) {
        cin >> y[i].first;
        y[i].second = i;
    }
    sort(y + 1, y + C + 1);
    vector<pair<int, int> > X;
    for (int i = 1; i <= N; ++i) {
        if (i & 1) {
            for (int j = 1; j <= M; ++j) X.push_back(make_pair(i, j));
        } else {
            for (int j = M; j >= 1; --j) X.push_back(make_pair(i, j));
        }
    }
    int j = C;
    for (int i = 0; i < N * M; ++i) {
        if (y[j].first == 0) --j;
        --y[j].first;
        x[X[i].first][X[i].second] = y[j].second;
    }
    for (int i = N; i >= 1; --i) {
        for (int j = 1; j <= M; ++j) cout << x[i][j];
        cout << endl;
    }
    return 0;
}
