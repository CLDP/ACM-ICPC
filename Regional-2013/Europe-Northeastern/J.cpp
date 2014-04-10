#include <vector>
#include <cstring>
#include <cstdio>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

const int MAXN = 50010;

int f[MAXN];

int main() {
    freopen("join.in", "r", stdin);
    freopen("join.out", "w", stdout);
    
    int N;
    cin >> N;
    string P;
    getline(cin, P);
    map<string, pair<int, int> > C;
    pair<int, int> ans = make_pair(0, 0);
    for (int i = 0; i < N; ++i) {
        getline(cin, P);
        istringstream PIN(P);
        string Q;
        PIN >> Q;
        Q = Q.substr(1, Q.size() - 2);
        
        f[i + 1] = 0;
        if (C.find(Q) == C.end()) C[Q] = make_pair(1, i + 1);
        if (C[Q].first > ans.first) ans = C[Q];
        
        string trash;
        while (PIN >> trash) {
            if (trash[0] != '@') continue; 
            string R = trash.substr(1, trash.size() - 1);
            
            if (C.find(R) == C.end()) continue;
            if (R == Q) continue;
            pair<int, int> temp = C[R];
            if (temp.first + 1 > C[Q].first) {
                C[Q] = make_pair(temp.first + 1, i + 1);
                f[i + 1] = temp.second;
            }
            if (C[Q].first > ans.first) ans = C[Q];
        }
    }
    cout << ans.first << endl;
    vector<int> A;
    int temp = ans.second;
    while (temp != 0) {
        A.push_back(temp);
        temp = f[temp];
    }
    for (int i = A.size() - 1; i >= 0; --i) {
        cout << A[i];
        if (i == 0) cout << endl; else cout << " ";
    }
    
    return 0;
}
