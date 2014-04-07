#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct node {
    long long D, R, P, G;
    bool operator < (node const &B) const {
        return D < B.D;
    }
};

node X[MAXN];

long double getT(pair<long long, long long> A, pair<long long, long long> B) {
    return 1.0 * (B.second - A.second) / (A.first - B.first);
}

int removeL(map<long long, long long> &S, const long long &D) {
    while (S.size() > 1) {
        map<long long, long long>::iterator iter = S.begin();
        pair<long long, long long> L1 = *iter, L2 = *(++iter);
        long double T = getT(L1, L2);
        if (T < D) {
            S.erase(S.begin());
            continue;
        } 
        break;
    }
    return 0;
}


int main() {
    int N, times = 0;
    long long CC, DD;
    while (cin >> N >> CC >> DD) {
        if (N == 0) break;
        
        for (int i = 0; i < N; ++i) cin >> X[i].D >> X[i].P >> X[i].R >> X[i].G;
        sort(X, X + N);
        
        map<long long, long long> S;
        S[0] = CC;
        
        for (int i = 0; i < N; ++i) {
            removeL(S, X[i].D - 1);
            
            map<long long, long long>::iterator iter = S.begin();
            
            iter = S.begin();
            long long B = iter->first * (X[i].D - 1) + iter->second;
            if (B < X[i].P) continue;
            B = B - X[i].P + X[i].R - X[i].G * X[i].D;
            
            if (S.find(X[i].G) != S.end() && S[X[i].G] >= B) continue;
            S[X[i].G] = B;
            
            bool flag = true;
            iter = S.find(X[i].G);
            map<long long, long long>::iterator iter2;
            if (iter != S.begin() && iter != (--S.end())) {
                iter2 = iter; --iter2;
                long double T1 = getT(*iter2, *iter);
                iter2 = iter; ++iter2;
                long double T2 = getT(*iter, *iter2);
                if (T1 > T2) {
                    S.erase(iter);
                    flag = false;
                }
            }
            
            if (flag && iter != S.begin()) {
                --iter;
                while (iter != S.begin()) {
                    iter2 = iter; ++iter2;
                    long double T2 = getT(*iter, *iter2);
                    iter2 = iter; --iter2;
                    long double T1 = getT(*iter2, *iter);
                    if (T1 <= T2) break;
                    S.erase(iter);
                    iter = iter2;
                }
            }
        }
        
        removeL(S, DD);
        map<long long, long long>::iterator iter = S.begin();
        cout << "Case " << ++times << ": " << iter->first * DD + iter->second << endl;
    }
    return 0;
}
