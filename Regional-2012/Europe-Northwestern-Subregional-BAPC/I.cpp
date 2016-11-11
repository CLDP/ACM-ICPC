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

char op[100005];

int main() {
    int n, t;
    cin >> t;
    while (t--) {
        scanf("%s", op);
        scanf("%d", &n);
        vector<int> v(n);
        char c;
        scanf(" %c", &c);
        for (int i = 0; i < n; ++i) scanf("%d%c", &v[i], &c);
        if (n == 0) scanf("%c", &c);
        int b = true;
        int l = 0, r = n - 1;
        int ll = strlen(op);
        for (int i = 0; i < ll; ++i) {
            if (op[i] == 'R')
                b = !b;
            else {
                if (b) ++l; else --r;
            }
        }
        if (l > r + 1)
            printf("error\n");
        else if (l == r + 1)
            printf("[]\n");
        else if (b) {
            printf("[%d", v[l]);
            for (int i = l + 1; i <= r; ++i) printf(",%d", v[i]);
            printf("]\n");
        } else {
            printf("[%d", v[r]);
            for (int i = r - 1; i >= l; --i) printf(",%d", v[i]);
            printf("]\n");
        }
    }

    return 0;
}
