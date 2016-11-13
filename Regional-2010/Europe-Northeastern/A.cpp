#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("alignment.in", "r", stdin);
    freopen("alignment.out", "w", stdout);
    vector<string> X[1010];
    string P;
    int N = 0;
    while (getline(cin, P)) {
        istringstream pin(P);
        while (pin >> P) X[N].push_back(P);
        ++N;
    }
    vector<int> T(200, 0);

    for (int j = 1; j < 200; ++j) {
        for (int i = 0; i < N; ++i) {
            if (X[i].size() < j) continue;
            T[j] = max(T[j], T[j - 1] + (int)X[i][j - 1].size() + 1);
        }
    }

    for (int i = 0; i < N; ++i) {
        int S = 0;
        for (int j = 0; j < X[i].size(); ++j) {
            if (S < T[j]) {
                while (S < T[j]) {
                    ++S;
                    cout << " ";
                }
            }
            cout << X[i][j];
            S += X[i][j].size();
        }
        cout << endl;
    }
    return 0;
}
