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
    int h, w, d, l;
};

bool r[102][102];
bool v[102][102][4][10];
string m[102];
string s;
vector<node> ns;
node tn;
int cnt, goal;
int h, w, l, sx, sy;

void push() {
    if ((m[tn.h][tn.w] != 'X') && !v[tn.h][tn.w][tn.d][tn.l]) {
        if ((tn.d == 0) && (tn.l == l - 1) && !r[tn.h][tn.w]) {
            r[tn.h][tn.w] = true;
            ++cnt;
        }
        ns.push_back(tn);
    }
}

int main() { 
    while (cin >> h >> w) {
        goal = h * w;
        memset(v, 0, sizeof(v));
        memset(r, 0, sizeof(r));
        for (int i = 0; i < h; ++i) {
            cin >> m[i];
            for (int j = 0; j < w; ++j)
                if (m[i][j] == 'E') {
                    sx = i;
                    sy = j;
                } else 
                if (m[i][j] == 'X') --goal;
        }
        cin >> l >> s;
        
        ns.clear();
        tn.h = sx;
        tn.w = sy;
        r[sx][sy] = true;
        cnt = 1;
        for (tn.d = 0; tn.d < 4; ++tn.d)
            for (tn.l = 0; tn.l < l; ++tn.l) {
                v[tn.h][tn.w][tn.d][tn.l] = true;
                ns.push_back(tn);
            }
        
        while (!ns.empty()) {
            tn = ns.back();
            ns.pop_back();
            
            char c = s[tn.l];
            tn.l = (tn.l - 1 + l) % l;
            switch (c) {
                case 'S':
                    if (tn.d == 0) {
                        if (tn.h == 0)
                            push();
                        else 
                        if (m[tn.h-1][tn.w] == 'X') push();
                        if (tn.h + 1 < h) {
                            tn.h++;
                            push();
                        }
                    } else 
                    if (tn.d == 1) {
                        if (tn.w == w - 1)
                            push();
                        else 
                        if (m[tn.h][tn.w+1] == 'X') push();
                        if (tn.w > 0) {
                            --tn.w;
                            push();
                        }
                    } else 
                    if (tn.d == 2) {
                        if (tn.h == h - 1)
                            push();
                        else 
                        if (m[tn.h+1][tn.w] == 'X') push();
                        if (tn.h > 0) {
                            --tn.h;
                            push();
                        }
                    } else 
                    if (tn.d == 3) {
                        if (tn.w == 0)
                            push();
                        else 
                        if (m[tn.h][tn.w-1] == 'X') push();
                        if (tn.w + 1 < w) {
                            ++tn.w;
                            push();
                        }
                    }
                    break;
                    
                case 'L':
                    tn.d = (tn.d + 1) % 4;
                    push();
                    break;
                    
                case 'R':
                    tn.d = (tn.d + 3) % 4;
                    push();
                    break;
            }
        }
        
        if (cnt == goal)
            cout << "OK" << endl;
        else
            cout << cnt << endl;
    }
    
    return 0;
}
