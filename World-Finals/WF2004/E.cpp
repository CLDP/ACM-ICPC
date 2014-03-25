#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MONTH[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool z[150000];

bool checkY(int Y) {
    if (Y % 4 == 0) {
        if (Y % 100 == 0) {
            if (Y % 400 == 0) return true; 
            return false;
        } 
        return true;
    }
    return false;
}


int StoI(string P) {
    int Y = 0, M = 0, D = 0;
    for (int i = 0; i < 4; ++i) Y = Y * 10 + (P[i] - '0');
    M = (P[4] - '0') * 10 + (P[5] - '0');
    D = (P[6] - '0') * 10 + (P[7] - '0');
    
    int ans = 0;
    for (int i = 1700; i < Y; ++i) {
        if (checkY(i)) ans += 366; else ans += 365;
    }
    for (int i = 1; i < M; ++i) {
        ans += MONTH[i];
        if (checkY(Y) && i == 2) ++ans;
    }
    ans += D;
    return ans;
}

string ItoSH(int D) {
    string P;
    while (D > 0) {
        char Q = (D % 10 + '0');
        P = Q + P;
        D /= 10;
    }
    return P;
}

string ItoS(int T) {
    int Y = 0, M = 0, D = 0;
    for (int i = 1700; i <= 2100; ++i) {
        Y = 365 + checkY(i);
        if (T > Y) {
            T -= Y;
        } else {
            Y = i;
            break;
        }
    }
    for (int i = 1; i <= 12; ++i) {
        M = MONTH[i] + (i == 2 && checkY(Y));
        if (M < T) {
            T -= M;
        } else {
            M = i;
            break;
        }
    }
    D = T;
    string ans = ItoSH(M) + "/" + ItoSH(D) + "/" + ItoSH(Y);
    return ans;
}


int main() {
    int N, M, times = 0;
    bool first = true;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;
        if (!first) cout << endl;
        first = false;
        vector<pair<int, int> > X, Y;
        int minD = 200000, maxD = 0;
        for (int i = 0; i < N; ++i) {
            string P, Q;
            cin >> P >> Q;
            X.push_back(make_pair(StoI(P), StoI(Q)));
            minD = min(minD, X[i].first);
            maxD = max(maxD, X[i].second);
        }
        for (int i = 0; i < M; ++i) {
            string P, Q;
            cin >> P >> Q;
            Y.push_back(make_pair(StoI(P), StoI(Q)));
            minD = min(minD, Y[i].first);
            maxD = max(maxD, Y[i].second);
        }
        
        memset(z, 0, sizeof(z));
        for (int i = 0; i < M; ++i) 
         for (int j = Y[i].first; j <= Y[i].second; ++j) z[j] = true;
        
        for (int i = 0; i < N; ++i) 
         for (int j = X[i].first; j <= X[i].second; ++j) z[j] = false;
        
        int total = 0;
        cout << "Case " << ++times << ":" << endl;
        for (int i = minD; i <= maxD; ++i) {
            if (!z[i]) continue;
            int j = i;
            while (z[j]) ++j;
            string P = ItoS(i), Q = ItoS(j - 1);
            if (i == j - 1) {
                cout << "    " << P << endl;
            } else {
                cout << "    " << P << " to " << Q << endl;
            }
            ++total;
            i = j - 1;
        }
        if (total == 0) {
            cout << "    No additional quotes are required." << endl;
        }
    }
   
    return 0;
}
