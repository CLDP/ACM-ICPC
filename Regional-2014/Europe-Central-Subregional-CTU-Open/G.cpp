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


int main() {
    string P;
    while (cin >> P) {
        if (P == "0") {
            cout << "1" << endl;
            continue;
        }
        if (P == "11") {
            cout << 0 << endl;
            continue;
        }
        int N = P.size();
        int i;
        bool flag = false;
        if (N & 1) {
            for (i = N - 1; i > 0; i -= 2) {
                if (P[i - 1] == '0' && P[i] == '1') {
                    P[i - 1] = '1';
                    P[i] = '0';
                } else
                if (P[i - 1] == '0' && P[i] == '0') {
                    P[i] = '1';
                    flag = true;
                    break;
                } else
                if (P[i - 1] == '1' && P[i] == '0') {
                    P[i] = '1';
                    flag = true;
                    break;
                } else
                
                if (P[i - 1] == '1' && P[i] == '1') {
                    P[i] = P[i - 1] = '0';
                    flag = true;
                    break;
                }
            }
            if (flag) {
                cout << P << endl;
            } else {
                P[0] = '0';
                P = "11" + P;
                cout << P << endl;
            }
        } else {
            for (i = N - 1; i > 0; i -= 2) {
                if (P[i - 1] == '0' && P[i] == '1') {
                    P[i - 1] = '1';
                    P[i] = '0';
                } else
                if (P[i - 1] == '0' && P[i] == '0') {
                    P[i] = '1';
                    flag = true;
                    break;
                } else
                if (P[i - 1] == '1' && P[i] == '0') {
                    P[i] = '1';
                    flag = true;
                    break;
                } else
                
                if (P[i - 1] == '1' && P[i] == '1') {
                    P[i] = P[i - 1] = '0';
                    flag = true;
                    break;
                }
            }
            if (P[0] == '0') {
                cout << P.substr(2, P.size() - 2) << endl;
            } else {
                cout << P << endl;
            }
        }
    }
    return 0;
}
