#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 100012398;

int x[4];
int y[4];
int yy[4];
bool z[4];
bool zz[4];
vector<int> ans;


int get(int a, int b, int p) {
    if (p == 0) {
        return a+b;
    } else 
    if (p == 1) {
        return a-b;
    } else 
    if (p == 2) {
        return a*b;
    } else 
    if (p == 3) {
        if (b == 0) return INF;
        if (a % b == 0) return a / b; else return INF;
    }
}


int check() {
    int now, now2;
    //----------------------------------
    now = get(x[y[0]], x[y[1]], yy[0]);
    if (now != INF) {
        now = get(now, x[y[2]], yy[1]);
        if (now != INF) {
            now = get(now, x[y[3]], yy[2]);
            if (now != INF) ans.push_back(now);
        }
    }
    //----------------------------------
    now = get(x[y[0]], x[y[1]], yy[0]);
    if (now != INF) {
        now2 = get(x[y[2]], x[y[3]], yy[2]);
        if (now2 != INF) {
            now = get(now, now2, yy[1]);
            if (now != INF) ans.push_back(now);
        }
    }
    //----------------------------------
    now = get(x[y[1]], x[y[2]], yy[1]);
    if (now != INF) {
        now = get(x[y[0]], now, yy[0]);
        if (now != INF) {
            now = get(now, x[y[3]], yy[2]);
            if (now != INF) ans.push_back(now);

        }
    }
    //----------------------------------
    now = get(x[y[1]], x[y[2]], yy[1]);
    if (now != INF) {
        now = get(now, x[y[3]], yy[2]);
        if (now != INF) {
            now = get(x[y[0]], now, yy[0]);
            if (now != INF) ans.push_back(now);

        }
    }
    //----------------------------------
    now = get(x[y[2]], x[y[3]], yy[2]);
    if (now != INF) {
        now = get(x[y[1]], now, yy[1]);
        if (now != INF) {
            now = get(x[y[0]], now, yy[0]);
            if (now != INF) ans.push_back(now);
        }
    }
}


int dfs2(int a) {
    if (a == 3) {
        check();
    } else 
    for (int i = 0; i < 4; ++i) {
         yy[a] = i;
         dfs2(a+1);
    }
}


int dfs(int a) {
    if (a == 4) {
        dfs2(0);
    } else 
    for (int i = 0; i < 4; ++i)
     if (!z[i]) {
         z[i] = true;
         y[a] = i;
         dfs(a+1);
         z[i] = false;
     }
}


int main() {
    int a, b, c, d, tt = 0;
    cin >> x[0] >> x[1] >> x[2] >> x[3];
    while (x[0] || x[1] || x[2] || x[3]) {
        ans.clear();
        ++tt;
        cout << "Case " << tt << ": ";
        dfs(0);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        int a = 1, b = ans[0], c = ans[0], d = 1;
        for (int i = 1; i < ans.size(); ++i) {
            if (ans[i] == ans[i-1] + 1) 
                ++d;
            else {
                if (d >= a) {
                    a = d;
                    c = ans[i-1];
                    b = c-d+1;
                }
                d = 1;
            }
                
        }
        if (d >= a) {
            a = d;
            c = ans[ans.size() - 1];
            b = c - d + 1;
        }
        cout << b << " to " << c << endl;
        cin >> x[0] >> x[1] >> x[2] >> x[3];
    }

    return 0;
}
