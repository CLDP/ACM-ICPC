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

long long X[20];


long long cal(long long A) {
    if (A < 10) return (1 + A) * A / 2;
    
    long long T = 1;
    int i = 0;
    while (T <= A) {
        T *= 10;
        ++i;
    }
    T /= 10;
    --i;
    int a = A / T;
    return X[i] * a + (1 + a - 1) * (a - 1) / 2 * T + a * (A % T + 1) + cal(A % T);
}


int main() {
    X[1] = 45;
    long long T = 10;
    for (int i = 2; i < 17; ++i) {
        X[i] = T * X[1] + 10 * X[i - 1];
        T *= 10;
    }

    long long A, B;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A >> B;
        cout << cal(B) - cal(max(0LL, A - 1)) << endl;
    }
    return 0;
}
