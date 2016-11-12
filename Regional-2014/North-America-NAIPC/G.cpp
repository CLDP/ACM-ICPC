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

int CNT[26];
int CC[26];
int NN[210];
map<string, bool> CT;

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}


int Get_Next(const string &P) {
    int j = 0, k = -1;
    NN[0] = -1;
    while (j < P.size()) 
     if (k == -1 || P[j] == P[k]) {
         NN[++j] = ++k;
     } else k = NN[k];
    return 0;
}


bool check(const string &P, const string &Q) {
    if (CT.find(P + Q) != CT.end()) return CT[P + Q];
    if (Q == "*") return true;
    
    int lenp = P.size(), lenq = Q.size();
    Get_Next(P);
    int i = 0, j = 0;
    while (i < lenp && j < lenq)
     if (i == -1 || P[i] == Q[j]) {
         ++i;
         ++j;
         if (i == lenp - 1) {
             if (check(P, Q.substr(0, j - i) + Q.substr(j, Q.size()))) return CT[P + Q] = true;
         }
     } else i = NN[i];
    
    return CT[P + Q] = false;
}

int main() {
    string P;
    cin >> P;
    int N = P.size();
    for (int i = 0; i < N; ++i) ++CNT[P[i] - 'a'];
    int L = -1;
    for (int i = 0; i < 26; ++i) {
        if (CNT[i] == 0) continue;
        if (L == -1) L = CNT[i]; else L = gcd(L, CNT[i]);
    }
    
    string ans;
    set<string> S;
    // Total length N
    // segment number T
    // segment length N / T
    for (int T = L; T >= 2; --T) {
        if (L % T != 0) continue;
        memset(CC, 0, sizeof(CC));
        for (int i = 0; i < N / T; ++i) ++CC[P[i] - 'a'];
        for (int i = 0; i < N - N / T + 1; ++i) {
            bool flag = true;
            for (int j = 0; j < 26; ++j) flag &= (CC[j] * T == CNT[j]);
            if (flag) {
                string Q = P.substr(i, N / T);
                if (S.find(Q) == S.end()) {
                    S.insert(Q);
                    Q = Q + "#";
                    Get_Next(Q);
                    if (check(Q, P.substr(0, i) + P.substr(i + N / T, P.size()) + "*")) {
                        if (ans == "") ans = Q.substr(0, Q.size() - 1);
                        if (Q.substr(0, Q.size() - 1) < ans) ans = Q.substr(0, Q.size() - 1);
                    }
                }
            }
            if (i < N - N / T) {
                --CC[P[i] - 'a'];
                ++CC[P[i + N / T] - 'a'];
            }
        }
        if (ans != "") break;
    }
    if (ans == "") ans = P;
    
    cout << ans << endl;
    return 0;
}
