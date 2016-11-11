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
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        int A, a;
        bool flag = true;
        scanf("%d", &A);
        for (int j = 0; j < A; ++j) {
            scanf("%d", &a);
            flag &= (a % 3 == 0);
        }
        cout << "Case #" << i << ": ";
        if (flag) cout << "Yes" << endl; else cout << "No" << endl;

    }
    return 0;
}
