#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    long long N, K;
    vector<int> A;
    
    cin >> N >> K;
    while (N > 0) {
        A.push_back(N % K);
        N = N / K;
    }
    long long res = 1, t = 0;
    bool free = false;
    int i = A.size() - 1;
    if (i % 2 == 1) {
        --i;
        free = true;
    } else {
        res = A[i];
        --i;
        if ((i > 0) && (A[i] > 0)) free = true;
        --i;
        t = 1;
    }
    while (i >= 0) {
        res *= K;
        if (free)
            t *= K;
        else {
            res += t * A[i];
            t = 1;
        }
        --i;
        if ((i > 0) && (A[i] > 0)) free = true;
        --i;
    }
    
    cout << res + t << endl;
    
    return 0;
}
