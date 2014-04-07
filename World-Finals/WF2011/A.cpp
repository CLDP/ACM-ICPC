#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

bool nonzero(const vector<long long> &R, int A, int B) {
    long long ans = 0;
    for (int i = A; i < B; ++i) ans += R[i];
    return ans > 0;
}

vector<pair<int, int> > mergeX(const vector<pair<int, int> > &X) {
    if (X.empty()) return X;
    
    vector<pair<int, int> > Y;
    int N = 0;
    Y.push_back(X[0]);
    for (int i = 1; i < X.size(); ++i) {
        if (X[i].second == Y[N].second) {
            Y[N].first += X[i].first;
        } else {
            Y.push_back(X[i]);
            ++N;
        }
    }
    return Y;
}

bool small(const vector<pair<int, int> > &X, const vector<pair<int, int> > &Y) {
    int XL = 0, YL = 0;
    for (int i = 0; i < X.size(); ++i) XL += X[i].first;
    for (int i = 0; i < Y.size(); ++i) YL += Y[i].first;
    if (XL != YL) return XL < YL;
    
    for (int i = 0; i < X.size(); ++i) {
        if (X[i] == Y[i]) continue;
        if (X[i].second != Y[i].second) return X[i].second > Y[i].second;
        if (X[i].second == 1) 
            return X[i].first > Y[i].first;
        else
            return X[i].first < Y[i].first;
    }
    return false;
}

int main() {
    int times = 0;
    long long a, m, p, q, r, s;
    while (cin >> a >> m >> p >> q >> r >> s) {
        if (a == 0) break;
        cout << "Case " << ++times << ":";
        if (m == 1) {
            long long D = (r - p) / a;
            if (p + a * D < r) ++D;
            if (q + a * D > s) {
                cout << " impossible" << endl;
            } else {
                if (D == 0) {
                    cout << " empty" << endl;
                } else {
                    cout << " " << D << "A" << endl;
                }
            }
            continue;
        }
        
        long long BASE = 1;
        bool no_solution = true;
        vector<pair<int, int> > ANS;
        for (int i = 0; i <= 30; ++i) {
            if (BASE > INF) break;
            if (s - q * BASE < 0) break;
            long long rr = (r - p * BASE + a - 1) / a, ss = (s - q * BASE) / a;
            if (rr < 0) rr = 0;
            if (rr > ss) {
                BASE = BASE * m;
                continue;
            }
            
            vector<long long> R, S;
            for (int j = 0; j < i; ++j) {
                R.push_back(rr % m);
                S.push_back(ss % m);
                rr /= m;
                ss /= m;
            }
            R.push_back(rr);
            S.push_back(ss);
            
            bool flag = true;
            vector<pair<int, int> > X;
            for (int j = i; j >= 0; --j) {
                if (R[j] != S[j]) {
                    int temp = R[j] + nonzero(R, 0, j);
                    if (flag && temp > 0) X.push_back(make_pair(temp, 1));
                    flag = false;
                } else {
                    if (flag && R[j] > 0) X.push_back(make_pair(R[j], 1));
                }
                if (j != 0) X.push_back(make_pair(1, 0));
            }
            
            X = mergeX(X);
            
            if (no_solution) {
                no_solution = false;
                ANS = X;
            } else {
                if (small(X, ANS)) ANS = X;
            }
            
            BASE = BASE * m;
        }
        
        if (no_solution) {
            cout << " impossible" << endl;
            continue;
        }
        if (ANS.empty()) {
            cout << " empty" << endl;
            continue;
        }
        for (int i = 0; i < ANS.size(); ++i) {
            cout << " " << ANS[i].first;
            if (ANS[i].second == 0) cout << "M"; else cout << "A";
        }
        cout << endl;
    }
    return 0;
}
