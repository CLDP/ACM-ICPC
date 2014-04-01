#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10010;
const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};


map<pair<int, int>, int> coll;
set<pair<int, int> > bd[N];
int f[N], xx[N], yy[N];
       
int find(int a) {
    if (f[a] != a) f[a] = find(f[a]);
    return f[a];
}
       
int del(int x, int y) {
    queue<pair<int, int> > Q;
    queue<int> T;
    Q.push(make_pair(x, y));
    T.push(coll[make_pair(x, y)]);
    coll.erase(make_pair(x, y));
    while (!Q.empty()) {
        pair<int, int> cur = Q.front();
        Q.pop();
        int cut = T.front();
        T.pop();
        int x = cur.first, y = cur.second, id = cut & 1;
        for (int i = 0; i < 4; ++i) {
            int cx = x + MX[i], cy = y + MY[i];
            if (cx > 0 && cy > 0) {
                pair<int, int> pos = make_pair(cx, cy);
                if (coll.count(pos) == 0) continue;
                int cd = coll[pos];
                if ((id & 1) == (cd & 1)) {
                    Q.push(pos);
                    T.push(cd);
                    coll.erase(pos);
                } else {
                    bd[find(cd)].insert(cur);
                }
            }            
        }
    }
    return 0;
}
       
int main() {
    int times;
    cin >> times;
    while (times--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i) {
            f[i] = i;
            bd[i].clear();
            cin >> xx[i] >> yy[i];
        }
        coll.clear();
        for (int j = 0; j < N; ++j) {
            int x = xx[j], y = yy[j];
            pair<int, int> ts = make_pair(x, y);
            coll[ts] = j;
            for (int i = 0; i < 4; ++i) {
                int cx = x + MX[i], cy = y + MY[i];
                if (cx > 0 && cy > 0) {
                    pair<int, int> pos = make_pair(cx, cy);
                    if (coll.count(pos) == 0) {
                        bd[find(j)].insert(pos);
                    } else {
                        int id = coll[pos];
                        int of = find(id);
                        int fa = find(j);
                        
                        bd[of].erase(ts);
       
                        if ((id & 1) == (j & 1)) {
                            f[fa] = of;
                            set<pair<int, int> >::iterator iter;
                            for (iter = bd[fa].begin(); iter != bd[fa].end(); ++iter) bd[of].insert(*iter);
                        } else {
                            if (bd[of].empty()) del(cx, cy);
                        }
                    }
                }
            }
            int fa = find(j);
            if (bd[fa].empty()) del(x, y);
        }
        
        int total = 0, bk = 0;
        map<pair<int, int>, int>::iterator iter;
        for (iter = coll.begin(); iter != coll.end(); ++iter) {
            ++total;
            bk += iter->second & 1;
        }
        cout << total - bk << " " << bk << endl;
    }
    return 0;
}
