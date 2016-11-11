#include <stdio.h>

int v[5000005];

int main() {
    int n, a, t;
    
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt) {
        scanf("%d", &n);
        for (int i = 1; i <= n + 2; ++i) v[i] = 0;
        int res = 0, ind = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a);
            v[a] = 1;
            if (ind < a - 1) ++res;
            while (v[ind+1] == 1) ++ind;
        }
        
        printf("Case #%d: %d\n", tt, res);
    }

    return 0;
}
