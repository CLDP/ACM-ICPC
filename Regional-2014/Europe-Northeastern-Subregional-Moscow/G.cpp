#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int cnt = 1;
unordered_map<string, int> m;
bool isF[200005];
int f[200005];
vector<string> v;
int ufs[200005];
int r[200005];

int ff(int i) {
    int j = i, t;
    while (ufs[i] > 0) i = ufs[i];
    while (j != i) {
        t = ufs[j];
        ufs[j] = i;
        j = t;
    }
    return i;
}

void join(int i, int j) {
    if (ufs[i] < ufs[j]) {
        ufs[i] += ufs[j];
        ufs[j] = i;
    } else {
        ufs[j] += ufs[i];
        ufs[i] = j;
    }
}

int main() {
    int n;
    int res = 2;
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string family, s, son, father;
        
        cin >> family >> son >> s >> s >> father;
        if (son == father) father = "!!!";
        son = family + " " + son;
        father = family + " " + father;
        int sid, fid;
        if (m.find(son) != m.end())
            sid = m[son];
        else {
            sid = cnt++;
            m[son] = sid;
            v.push_back(son);
            ufs[sid] = -1;
        }
        if (m.find(father) != m.end())
            fid = m[father];
        else {
            fid = cnt++;
            m[father] = fid;
            v.push_back(father);
            ufs[fid] = -1;
        }
        isF[fid] = true;
        f[sid] = fid;
        if (ff(sid) == ff(fid)) {
            int cid = fid, cur = 2;
            while (cid != sid) {
                cur++;
                cid = f[cid];
            }
            res = max(cur, res);
            cid = fid;
            while (cid != sid) {
                r[cid] = cur;
                cid = f[cid];
            }
            r[cid] = cur;
        }
        else
            join(ff(sid), ff(fid));
    }
      
    for (int i = 1; i < cnt; ++i) {
        if (isF[i] || (r[i] > 0)) continue;
        int cur = 2;
        int cid = f[i];
        while ((f[cid] != 0) && (r[cid] == 0)) {
            cur++;
            cid = f[cid];
        }
        if (r[cid] > 0) cur += r[cid] - 1;
        res = max(cur, res);
        r[i] = cur;
        int tmp = cur;
        cid = f[i];
        while ((f[cid] != 0) && (r[cid] == 0)) {
            r[cid] = --tmp;
            cid = f[cid];
        }
    }
    
    cout << res - 1 << endl;

    return 0;
}
