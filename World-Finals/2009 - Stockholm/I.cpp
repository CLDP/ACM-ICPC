#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;

double width[MAXN], height[MAXN], x[MAXN], y[MAXN];
double nx[MAXN], ny[MAXN], nwidth[MAXN], nheight[MAXN];
int H[MAXN], V[MAXN], U[MAXN], D[MAXN], L[MAXN], R[MAXN];
int C[MAXN], outer[MAXN];

bool cmp(const int &a, const int &b) {
    return x[a] + y[a] < x[b] + y[b];
}

int main() {
    int N, M, times = 0;
    while (cin >> N >> M >> width[0] >> height[0]) {
        if (N == 0) break;
        ++times;
        x[0] = y[0] = nx[0] = ny[0] = C[0] = 0;
        for (int i = 1; i <= N; ++i) {
            cin >> x[i] >> y[i] >> width[i] >> height[i];
            cin >> H[i] >> V[i] >> U[i] >> D[i] >> L[i] >> R[i];
            if (H[i] + L[i] + R[i] == 0) R[i] = 1;
            if (V[i] + U[i] + D[i] == 0) U[i] = 1;
            C[i] = i;
        }
        sort(C + 1, C + N + 1, cmp);
        
        for (int i = 1; i <= N; ++i)
         for (int j = i - 1; j >= 0; --j)
          if (x[C[j]] < x[C[i]] && y[C[j]] < y[C[i]] && x[C[j]] + width[C[j]] > x[C[i]] + width[C[i]]
           && y[C[j]] + height[C[j]] > y[C[i]] + height[C[i]]) {
              outer[C[i]] = C[j];
              break;
          }
        for (int i = N; i > 0; --i) {
            x[C[i]] -= x[outer[C[i]]];
            y[C[i]] -= y[outer[C[i]]];
        }
        for (int q = 1; q <= M; ++q) {
            cin >> nwidth[0] >> nheight[0];
            for(int i = 1; i <= N; ++i) {
                int cur = C[i];
                double w0 = 0, h0 = 0;
                if (!H[cur]) w0 += width[cur];
                if (!V[cur]) h0 += height[cur];
                if (!U[cur]) h0 += y[cur];
                if (!D[cur]) h0 += height[outer[cur]] - height[cur] - y[cur];
                if (!L[cur]) w0 += x[cur];
                if (!R[cur]) w0 += width[outer[cur]] - width[cur] - x[cur];
                if (H[cur])
                    nwidth[cur] = width[cur] * (nwidth[outer[cur]] - w0) / (width[outer[cur]] - w0);
                else
                    nwidth[cur] = width[cur];
                if (V[cur])
                    nheight[cur] = height[cur] * (nheight[outer[cur]] - h0) / (height[outer[cur]] - h0);
                else
                    nheight[cur] = height[cur];
                if (U[cur])
                    ny[cur] = y[cur] * (nheight[outer[cur]] - h0) / (height[outer[cur]] - h0);
                else
                    ny[cur] = y[cur];
                if (L[cur])
                    nx[cur] = x[cur] * (nwidth[outer[cur]] - w0) / (width[outer[cur]] - w0);
                else
                    nx[cur] = x[cur];
            }
            for (int i = 1; i <= N; ++i) {
                nx[C[i]] += nx[outer[C[i]]];
                ny[C[i]] += ny[outer[C[i]]];
            }
            cout << "Case " << times << ", resize operation " << q << ":" << endl;
            for (int i = 1; i <= N; ++i) 
             cout << "    Window " << i << ", x = " << round(nx[i]) << ", y = " << round(ny[i])
                  << ", width = " << round(nwidth[i]) << ", height = " << round(nheight[i]) << endl;
        }
    }
    return 0;
}
