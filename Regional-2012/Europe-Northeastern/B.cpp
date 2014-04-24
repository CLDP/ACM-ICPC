#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long w[22];
long long f[1050000];
int ind[1050000];

int main() {
    long long N, C, T, k = 0, newt;
    cin >> N >> C >> T;
    cout << "accept" << endl;
    
    ind[1] = 0;
    for (int i = 2; i <= 1049000; i *= 2) ind[i] = ind[i / 2] + 1;
    
    while (T != 0) {
        cin >> newt;
        if (newt < T) {
            T = newt;
            cout << "accept" << endl;
        } else
            cout << "decline" << endl;
    }
    
    while (k < N) {
        cin >> newt;
        if (newt > T) {
            w[k] = newt - T;
            ++k;
            if ((k == N) && (newt <= C)) {
                cout << "stop" << endl;
                return 0;
            }
            cout << "accept" << endl;
            T = newt;
        } else
            cout << "decline" << endl;
    }
    
    f[0] = 0;
    long long best = 0, bind = 0;
    for (int i = 1; i < (1 << N); ++i) {
        int j = i & (-i);
        int it = ind[j];
        f[i] = f[i - j] + w[it];
        if ((f[i] > best) && (f[i] <= C)) {
            best = f[i];
            bind = i;
        }
    }
    
    vector<long long> need;
    long long dind = ((1 << N) - 1) - bind;
    while (dind > 0) {
        int j = dind & (-dind);
        int it = ind[j];
        need.push_back(w[it]);
        dind = dind - j;
    }
    
    while (need.size() > 0) {
        cin >> newt;
        if (newt == best) {
            cout << "stop" << endl;
            return 0;
        }
        if (newt > T)
            cout << "decline" << endl;
        else {
            int tw = T - newt;
            int i = 0;
            while ((i < need.size()) && (tw != need[i])) ++i;
            if (i < need.size()) {
                T = newt;
                need[i] = need[need.size() - 1];
                need.pop_back();
                cout << "accept" << endl;
            } else
                cout << "decline" << endl;
        }
    }
    
    return 0;
}
