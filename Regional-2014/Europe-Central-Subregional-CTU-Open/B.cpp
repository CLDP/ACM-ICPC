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

struct node {
    int a, b;
};

node ns[10000002];

int main() {
    int n, k;
    
    cin >> n;
    while (n--) {
        cin >> k;
        for (int i = 0; i < k; ++i)
            scanf("%d %d", &ns[i].a, &ns[i].b);
        int best = ns[k - 1].a - k + 1;
        int res = ns[k - 1].b - ns[k - 1].a;
        for (int y = k - 1; y >= 0; --y) {
            best = max(best, ns[y].a - y);
            res = min(res, ns[y].b - y - best);
        }
        best = ns[0].a;
        for (int y = 0; y < k; ++y) {
            best = max(best, ns[y].a + y);
            res = min(res, ns[y].b + y - best);
        }
        
        printf("K prechodu reky je treba %d pontonu.\n", res);
    }
    
    return 0;
}
