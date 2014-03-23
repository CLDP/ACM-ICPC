#include <numeric>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdio>
const int MAX_LEN = 50000;
using namespace std;


struct SuffixArray {
    int n;
    int m[2][MAX_LEN];
    // sa[0..n] = (0..n) saves which suffix is rank i, including last one (sa[0])
    // rank[0..n-1] = (1..n) saves this suffix's rank, start from 1
    // height[i (1..n)] is the longest prefix of sa[i-1], sa[i]
    int sa[MAX_LEN], rank[MAX_LEN], height[MAX_LEN];

    void indexSort(int sa[], int ord[], int id[], int nId) { 
        //ord is the ordering get from prev stage
        static int cnt[MAX_LEN];
        memset(cnt, 0, sizeof(0) * nId);

        for (int i = 0; i < n; ++i) ++cnt[id[i]];
        partial_sum(cnt, cnt + nId, cnt);
        for (int i = n - 1; i >= 0; --i) sa[--cnt[id[ord[i]]]] = ord[i];
    }
    
    void calheight(int r[], int sa[], int n) {
         int i, j, k = 0;
         for (i = 1; i <= n; i++) rank[sa[i - 1]] = i - 1;
         for (i = 0; i < n; height[rank[i++]] = k)
          for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
    }

    int *id, *oId;
    void init(int s[], int _n) { //s[n] == 0
        n = _n;
        static int w[MAX_LEN];
        memcpy(w, s, sizeof(int) * n);
        sort(w, w + n);
        int nId = unique(w, w + n) - w;
        id = m[0], oId = m[1];
        for (int i = 0; i < n; ++i) {
            id[i] = lower_bound(w, w + nId, s[i]) - w;
        }
        static int ord[MAX_LEN];
        for (int i = 0; i < n; ++i) ord[i] = i;
        indexSort(sa, ord, id, nId);
        for (int k = 1; k <= n && nId < n; k <<= 1) {
            //get the prev order
            // k -> k*2
            int cur = 0;
            for (int i = n - k; i < n; ++i) ord[cur++] = i;
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= k) ord[cur++] = sa[i] - k;
            }
            indexSort(sa, ord, id, nId);
            //get new id
            cur = 0;
            swap(oId, id);
            for (int i = 0; i < n; ++i) {
                int c = sa[i], p = i ? sa[i - 1] : 0;
                id[c] = (i == 0 || oId[c] != oId[p] || oId[c + k] != oId[p + k]) ? cur++ : cur - 1;
            }
            nId = cur;
        }
        calheight(s, sa, n);
    }
    
    // Add followings if needed
    int mm[MAX_LEN], best[20][MAX_LEN];
    void initRMQ() {
         int a, b;
         mm[0] = -1;
         for (int i = 1; i <= n; ++i)
             mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
         for (int i = 1; i <= n; ++i) best[0][i] = i;
         for (int i = 1; i <= mm[n]; ++i)
          for (int j = 1; j <= n + 1 - (1 << i); ++j) {
              a = best[i - 1][j];
              b = best[i - 1][j + (1 << (i - 1))];
              if (height[a] < height[b]) best[i][j] = a; else best[i][j] = b;
          }
    }
    
    int askRMQ(int a, int b){
        int t = mm[b - a + 1]; 
        b -= (1 << t) - 1;
        a = best[t][a];
        b = best[t][b];
        return height[a] < height[b] ? a : b;
    }
    
    int LCP(int a,int b) {
        a = rank[a];
        b = rank[b];
        if (a > b) swap(a, b);
        return height[askRMQ(a + 1, b)];
    }
    
} sa;



int x[MAX_LEN];
char p[MAX_LEN];

int main() {
    int T;
    while (cin >> T) {
        if (T == 0) break;
        scanf("%s", p);
        int N = strlen(p);
        for (int i = 0; i < N; ++i) x[i] = p[i] - 'a' + 1;
        x[N] = 0;
        
        if (T == 1) {
            cout << N << " " << 0 << endl;
            continue;
        }
        
        // N + 1 (x[N]) must be a useless smallest last value
        sa.init(x, N + 1);
        
        int ans1 = 0, ans2 = -1;
        multiset<int> len;
        set<int> pos;
        
        pos.insert(sa.sa[1]);
        for (int i = 2; i <= T; ++i) {
            len.insert(sa.height[i]);
            pos.insert(sa.sa[i]);
        }
        
        if (*len.begin() > ans1) {
            ans1 = *len.begin();
            ans2 = *pos.rbegin();
        }
        
        for (int i = T + 1; i <= N; ++i) {
            len.erase(len.find(sa.height[i - T + 1]));
            pos.erase(pos.find(sa.sa[i - T]));
            len.insert(sa.height[i]);
            pos.insert(sa.sa[i]);
            if (*len.begin() > ans1) {
                ans1 = *len.begin();
                ans2 = *pos.rbegin();
            } else
            if (*len.begin() == ans1 && *pos.rbegin() > ans2) {
                ans2 = *pos.rbegin();
            }
        }
        
        if (ans1 == 0) {
            cout << "none" << endl;
        } else {
            cout << ans1 << " " << ans2 << endl;
        }
    }
    return 0;
}
