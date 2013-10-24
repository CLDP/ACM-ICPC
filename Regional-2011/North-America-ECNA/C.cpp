#include <cstdio>

int main() {
    int n, m, nn = 0;
    int x[501][2501];
    scanf("%d%d", &n, &m);
    while (n != 0 && m != 0) {
        ++nn;
        int a;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &a);
                x[i][a] = j;
            }
        }
        int b, c;
        a = 0;
        for (int i = 1; i < m; ++i) {
            b = c = 0;
            for (int j = 0; j < n; ++j) 
             if (x[j][i] < x[j][a]) 
                 ++c;
             else 
                 ++b;
             if (c > b) a = i;
        }
        bool flag = true;
        for (int i = 0; i < m; ++i)
         if (i != a) {
            b = c = 0;
            for (int j = 0; j < n; ++j) 
             if (x[j][i] < x[j][a]) 
                 ++c;
             else 
                 ++b;
             if (c >= b) flag = false;
             if (!flag) break;
         }
        printf("Case %d: ", nn);
        if (flag)
            printf("%d\n", a); 
        else 
            printf("No Condorcet winner\n"); 

        scanf("%d%d", &n, &m);
    }

    return 0;
}
