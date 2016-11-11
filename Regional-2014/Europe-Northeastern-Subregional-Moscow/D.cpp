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
    int A, B;
    cin >> A >> B;
    for (int i = 1; i <= 200; ++i) {
        if (i * i + A * A == B * B || A * A + B * B == i * i) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
