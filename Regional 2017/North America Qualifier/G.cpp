#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <set>
using namespace std;

const int MAXN = 100010;

long long X[MAXN], Y[MAXN];
map<long long, set<long long> > S;

int main() {
    ios_base::sync_with_stdio(false);
    int N; 
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
        S[X[i]].insert(Y[i]);
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (S[X[i]].find(Y[i] - 2018) != S[X[i]].end()) ++ans;
        if (S[X[i]].find(Y[i] + 2018) != S[X[i]].end()) ++ans;
        if (S[X[i] + 2018].find(Y[i]) != S[X[i] + 2018].end()) ++ans;
        if (S[X[i] - 2018].find(Y[i]) != S[X[i] - 2018].end()) ++ans;

        if (S[X[i] - 1118].find(Y[i] + 1680) != S[X[i] - 1118].end()) ++ans;
        if (S[X[i] - 1118].find(Y[i] - 1680) != S[X[i] - 1118].end()) ++ans;
        if (S[X[i] + 1118].find(Y[i] + 1680) != S[X[i] + 1118].end()) ++ans;
        if (S[X[i] + 1118].find(Y[i] - 1680) != S[X[i] + 1118].end()) ++ans;


        if (S[X[i] - 1680].find(Y[i] + 1118) != S[X[i] - 1680].end()) ++ans;
        if (S[X[i] - 1680].find(Y[i] - 1118) != S[X[i] - 1680].end()) ++ans;
        if (S[X[i] + 1680].find(Y[i] + 1118) != S[X[i] + 1680].end()) ++ans;
        if (S[X[i] + 1680].find(Y[i] - 1118) != S[X[i] + 1680].end()) ++ans;

    }
    cout << ans / 2 << endl;
 
    return 0;
}
