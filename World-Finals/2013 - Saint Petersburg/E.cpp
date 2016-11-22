#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

int A, B, N, M;
vector<string> P;
vector<int> Q, Times, Fly, Start, End, C;
vector<long long> Len;
vector<pair<int, int> > S;
long long F[1010][14][14];
long long ansT = 1000000000000000;
int NN[14];



int calculate_F() {
    int M = S.size();
    Start = End = vector<int> (N, 0);
    for (int i = 0; i < M; ++i) {
        int prev = 0, a = S[i].first;
        for (int p = 0; p <= 13; ++p)
         for (int q = 0; q <= 13; ++q) F[a][p][q] = 0;
        
        Len[a] = 0;
        for (int j = S[i].first + 1; j < S[i].second; ++j) {
            if (Q[j] == 0) {
                ++F[a][prev][Start[j]];
                for (int p = 1; p <= 13; ++p)
                 for (int q = 1; q <= 13; ++q) F[a][p][q] += F[j][p][q] * Times[j];
                F[a][End[j]][Start[j]] += Times[j] - 1;
                if (Start[a] == 0) Start[a] = Start[j];
                if (End[j] != 0) {
                    prev = End[j];
                    End[a] = End[j];
                }
                Len[a] += Times[j] * Len[j];
                j = Fly[j];
            } else {
                ++Len[a];
                if (C[Q[j]] == 0) continue;
                ++F[a][prev][Q[j]];
                prev = Q[j];
                if (Start[a] == 0) Start[a] = Q[j];
                End[a] = Q[j];
            }
        }
    }
}


int dfs_num(int now, int up, long long ans) {
    if (now == M + 1) {   
        ans += Len[0];
        if (ansT > ans) ansT = ans;
    } else
    if (C[now] == 0) {
        dfs_num(now + 1, up, ans);
    } else
    for (int i = 1; i <= min(up, A - 1); ++i) {
        if (NN[i] == B) continue;
        ++NN[i];
        C[now] = i;
        long long temp = ans;
        for (int j = 1; j < now; ++j)
         if (C[j] != C[now] && C[j] != 0) temp += F[0][j][now] + F[0][now][j];
        dfs_num(now + 1, max(up, i + 1), temp);
        --NN[i];
        C[now] = -1;
    }
    return 0;
}


int dfs_0() {
    int num = min(B, M);
    for (int i = 1; i < (1 << M); ++i) {
        if (__builtin_popcount(i) != num) continue;
        for (int j = 0; j < M; ++j)
         if (i & (1 << j)) C[j + 1] = 0; else C[j + 1] = -1;
        calculate_F();
        dfs_num(1, 1, M > B);
    }
    return 0;
}


int main() {
    cin >> A >> B;
    P.push_back("R1");
    Q.push_back(0);
    set<int> SV;
    while (true) {
        string p;
        if (cin >> p) {
            P.push_back(p);
            if (p[0] == 'V') {
                Q.push_back(atoi(p.substr(1, p.size() - 1).c_str()));
                SV.insert(atoi(p.substr(1, p.size() - 1).c_str()));
            } else {
                Q.push_back(0);
            }
        } else {
            break;
        }
    }
    P.push_back("E");
    Q.push_back(0);
    
    N = P.size();
    int tempI = 1;
    for (set<int>::iterator iter = SV.begin(); iter != SV.end(); ++iter) {
        if (*iter == tempI) {
            ++tempI;
            continue;
        }
        for (int j = 0; j < N; ++j)
         if (Q[j] == *iter) Q[j] = tempI;
        ++tempI;
    }
    
    stack<int> sta;
    Times = Fly = vector<int> (N, 0);
    for (int i = 0; i < N; ++i) {
        if (P[i][0] == 'R') {
            sta.push(i);
            Times[i] = atoi(P[i].substr(1, P[i].size() - 1).c_str());
        }
        if (P[i][0] == 'E') {
            Fly[sta.top()] = i;
            S.push_back(make_pair(sta.top(), i));
            sta.pop();
        }
    }
    
    M = SV.size();
    C = vector<int> (M + 1, -1);
    Len = vector<long long> (N, 0);
    dfs_0();
    
    cout << ansT << endl;
    
    return 0;
}
