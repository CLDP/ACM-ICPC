#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

int gcd(int x, int y) {
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

struct point {
    int x, y;
};

vector<point> ps;
map<pair<int, int>, int> m;

int main() {
    int n, p;
    
    scanf("%d %d", &n, &p);
    ps.reserve(n);
    point tp;
    
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &tp.x, &tp.y);
        ps.push_back(tp);
    }
    
    int res = 0, need = (n * p - 1) / 100 + 1;
    int l = 0;
    while ((l < 40) && (res + 1 < need)) {
        l++;
        int b = rand() % n;
        m.clear();
        for (int i = 0; i < n; ++i) {
            if (b == i) continue;
            int dx = ps[b].x - ps[i].x;
            int dy = ps[b].y - ps[i].y;
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }
            int d = gcd(dx, abs(dy));
            dx = dx / d;
            dy = dy / d;
            pair<int, int> p = make_pair(dx, dy);
            ++m[p];
            res = max(res, m[p]);
        }
    }
    
    if (res + 1 < need)
        cout << "impossible" << endl;
    else
        cout << "possible" << endl;

    return 0;
}
