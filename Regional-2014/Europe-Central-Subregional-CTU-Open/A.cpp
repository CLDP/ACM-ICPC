#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    int w, n;
};

bool compare(node n1, node n2) {
    return n1.w > n2.w;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        int p, t;
        
        scanf("%d %d", &p, &t);
        vector<node> ns(t);
        for (int i = 0; i < t; ++i) {
            int c, s;
            scanf("%d %d", &c, &s);
            ns[i].n = c;
            ns[i].w = s * 6;
            if (c == 0) {
                ns.pop_back();
                --i;
                --t;
                continue;
            }
            set<pair<int, int> > m;
            for (int j = 0; j < s; ++j) {
                int x, y;
                scanf("%d %d", &x, &y);
                m.insert(make_pair(x, y));
                if (m.find(make_pair(x+1, y)) != m.end()) ns[i].w -= 2;
                if (m.find(make_pair(x-1, y)) != m.end()) ns[i].w -= 2;
                if (m.find(make_pair(x+1, y-1)) != m.end()) ns[i].w -= 2;
                if (m.find(make_pair(x-1, y+1)) != m.end()) ns[i].w -= 2;
                if (m.find(make_pair(x, y+1)) != m.end()) ns[i].w -= 2;
                if (m.find(make_pair(x, y-1)) != m.end()) ns[i].w -= 2;
            }
        }
        
        sort(ns.begin(), ns.end(), compare);
        
        int cnt = 0, res = 0;
        int ind = 0;
        if (ns[0].w >= p)
            printf("Je treba 1 celku.\n");
        else {
            res = 2;
            for (int i = 0; i < t; ++i) {
                if (res + (ns[i].w - 2) * ns[i].n >= p) {
                    cnt += (p - res + ns[i].w - 3) / (ns[i].w - 2);
                    res = p;
                    break;
                }
                cnt += ns[i].n;
                res += ns[i].n * (ns[i].w - 2);
            }
            if (res < p)
                printf("Kapacita zakladny je pouze %d lidi.\n", res);
            else
                printf("Je treba %d celku.\n", cnt);
        }
    }
    
    return 0;
}
