#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <cstdio>
using namespace std;

// MAXLEN must be at least twice as big as input length
const int MAXLEN = 200010;
const int LOGMAXLEN = 20;

class SA {
public: 
    int n;
    int s[MAXLEN];
    int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN];
    int rank[MAXLEN], height[MAXLEN];

    // In most cases, don't need to clear the array
    // Unless short string after long string, and t and t2 are corrupted
    void init(const char *ss) {
        // Length is size + 1
        n = strlen(ss) + 1;
        // Change the index here
        for (int i = 0; i < n; ++i) s[i] = ss[i];
        // Must guarantee that there is a smallest one at the end
        s[n] = 0;
    }

    // Build suffix array
    // All element in s must be between 0 and m - 1
    void build_sa(int m) {
        int *x = t, *y = t2;
        // Radix sort
        for (int i = 0; i < m; ++i) c[i] = 0;
        for (int i = 0; i < n; ++i) ++c[x[i] = s[i]];
        for (int i = 1; i < m; ++i) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n - k; i < n; ++i) y[p++] = i;
            for (int i = 0; i < n; ++i) if (sa[i] >= k) y[p++] = sa[i] - k;
            for (int i = 0; i < m; ++i) c[i] = 0;
            for (int i = 0; i < n; ++i) ++c[x[y[i]]];
            for (int i = 0; i < m; ++i) c[i] += c[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (int i = 1; i < n; ++i) 
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            if (p >= n) break;
            m = p;
        }

    }

    // height[i] is the LCP of sa[i - 1] and sa[i]
    // In this set up, height[0, 1] is useless
    // Because we know sa[0] is the artificial ending
    void getHeight() {
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (k) --k;
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k]) ++k;
            height[rank[i]] = k;
        }
    }

    int d[MAXLEN][LOGMAXLEN];
    void RMQ_init() {
        for (int i = 2; i < n; ++i) d[i][0] = height[i];
        for (int j = 1; (1 << j) < n; ++j) {
            for (int i = 2; i < n; ++i) {
                d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Longest Common Prefix
    // Do not ask for a == b
    int LCP(int a, int b) {
        a = rank[a];
        b = rank[b];
        if (a > b) swap(a, b);
        ++a;
        for (int i = 0; i < LOGMAXLEN; ++i) {
            if (a + (1 << (i + 1)) - 1 <= b) continue;
            return min(d[a][i], d[b - (1 << i) + 1][i]);
        }
        return 0;
    }
};

SA sa;

int main() {
    string P;
    cin >> P;
    sa.init(P.c_str());
    sa.build_sa(200);
    sa.getHeight();
    sa.RMQ_init();

    return 0;
}
