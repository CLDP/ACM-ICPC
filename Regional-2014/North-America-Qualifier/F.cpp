#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


long long gcd(long long A, long long B) {
    while (B != 0) {
        long long T = A % B;
        A = B;
        B = T;
    }
    return A;
}

int main() {
    long long A, B, C;
    while (cin >> A >> B) {
        if (A == 0 && B == 0) return 0;
        C = A / B;
        A = A - B * C;
        cout << C << " " << A << " / " << B << endl;
    }
    
    return 0;
}
