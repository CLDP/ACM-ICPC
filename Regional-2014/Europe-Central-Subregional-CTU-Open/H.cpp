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

const int MX[4] = {0, 1, 0, -1};
const int MY[4] = {1, 0, -1, 0};

int x[1000100];
int A[10], B[10], C[10], D[10];

bool check(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    if (x1 == x2) {
        if (x3 == x4) {
            if (x3 != x1) return false;
            return (y1 <= y3 && y3 <= y2) || (y1 <= y4 && y4 <= y2);
        } else {
            if (y1 <= y3 && y3 <= y2) {
                if (x3 <= x1 && x1 <= x4) return true;
            } else {
                return false;
            }
        }
    }
    if (y3 == y4) {
        if (y1 != y3) return false;
        return (x1 <= x3 && x3 <= x2) || (x1 <= x4 && x4 <= x2);
    } else {
        if (x1 <= x3 && x3 <= x2) {
            if (y3 <= y1 && y1 <= y4) return true;
        } else {
            return false;
        }
    }
    return false;
}

int main() {
    int N;
    while (cin >> N) {
        int a = 0, b = 0;
        for (int i = 0; i < N; ++i) scanf("%d", &x[i]);
        
        bool flag = true;
        for (int i = 0; i < N; ++i) {
            int k = i % 10;
            A[k] = a;
            B[k] = b;
            a += x[i] * MX[i % 4];
            b += x[i] * MY[i % 4];
            C[k] = a;
            D[k] = b;
            if (A[k] == C[k] && B[k] > D[k]) swap(B[k], D[k]);
            if (B[k] == D[k] && A[k] > C[k]) swap(A[k], C[k]);
            if (i < 10) {
                for (int j = 0; j < i - 1; ++j) {
                    if (check(A[k], B[k], C[k], D[k], A[j], B[j], C[j], D[j])) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) {
                    cout << i << endl;
                    break;
                }
            } else {
                for (int j = 0; j < 10; ++j) {
                    if (j == k) continue;
                    if (j == (k + 9) % 10) continue;
                    if (check(A[k], B[k], C[k], D[k], A[j], B[j], C[j], D[j])) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) {
                    cout << i << endl;
                    break;
                }
            }
        }
        
        if (flag) cout << "OK" << endl;
    }
    return 0;
}
