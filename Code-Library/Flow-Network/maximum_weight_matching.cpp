const int MAXN = 1001;
const int INF = 1000000000;

// z is the weight matrix input
int z[MAXN][MAXN];
bool x[MAXN], y[MAXN];
int lx[MAXN], ly[MAXN];

// l is the matching result, see below for usage
int l[MAXN];

bool find(int v, int M) {
    int k;
    x[v] = true;
    for (int i = 1; i <= M; ++i)
     if (!y[i] && lx[v] + ly[i] == z[v][i]) {
         y[i] = true;
         k = l[i];
         l[i] = v;
         if (k == 0 || find(k, M)) return true;
         l[i] = k;
     }
    return false;
}

int match(int N, int M) {
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    memset(l, 0, sizeof(l));

    for (int i = 1; i <= N; ++i) 
     for (int j = 1; j <= M; ++j)
      if (z[i][j] > lx[i]) lx[i] = z[i][j];
      
    for (int k = 1; k <= N; ++k) while (true) {
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        
        if (find(k, M)) break;
        int d = INF;
        for (int i = 1; i <= N; ++i) if (x[i])
         for (int j = 1; j <= M; ++j) if (!y[j])
          if (d > lx[i] + ly[j] - z[i][j]) d = lx[i] + ly[j] - z[i][j];
        
        for (int i = 1; i <= N; ++i)
         if (x[i]) lx[i] -= d;
        
        for (int j = 1; j <= M; ++j) 
         if (y[j]) ly[j] += d;
    }
    
    int flow = 0, cost = 0;
    for (int i = 1; i <= M; ++i)
     if (l[i] > 0) {
         ++flow;
         cost += z[l[i]][i];     
     }
    
    return 0;
}
