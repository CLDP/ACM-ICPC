#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;

struct node {
    int x, y, o;
};

int f[1005][1005][9];
char m[1005][1005];
vector<node> q;

int main() {
    int times, a, b;
    node st, en, tmp;
    
    cin >> times;
    while (times--) {
        cin >> a >> b;
        q.clear();

        for (int i = 0; i <= a; ++i)
         for (int j = 0; j <= b; ++j)
          for (int k = 0; k < 9; ++k) f[i][j][k] = -1;
        
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) {
                cin >> m[i][j];
                if (m[i][j] == 'R') {
                    st.x = i;
                    st.y = j;
                    st.o = 9;
                } else 
                if (m[i][j] == 'D') {
                    en.x = i;
                    en.y = j;
                    en.o = 9;
                }
            }
        }
        
        q.push_back(st);
        f[st.x][st.y][st.o] = 0;
        unsigned int n = 0;
        while (n < q.size()) {
            if ((q[n].x != 0) && (q[n].o != 4) && (q[n].o != 2) && (q[n].o != 6)) {
                tmp.x = q[n].x - 1;
                tmp.y = q[n].y;
                if (q[n].o == 0) tmp.o = 4; else tmp.o = 0;
                if ((f[tmp.x][tmp.y][tmp.o] == -1) && (m[tmp.x][tmp.y] != 'B')) {
                    q.push_back(tmp);
                    f[tmp.x][tmp.y][tmp.o] = f[q[n].x][q[n].y][q[n].o] + 1;
                    if ((tmp.x == en.x) && (tmp.y == en.y)) break;
                }
            }

            if ((q[n].x != a - 1) && (q[n].o != 6) && (q[n].o != 0) && (q[n].o != 4)) {
                tmp.x = q[n].x + 1;
                tmp.y = q[n].y;
                if (q[n].o == 2) tmp.o = 6; else tmp.o = 2;
                if ((f[tmp.x][tmp.y][tmp.o] == -1) && (m[tmp.x][tmp.y] != 'B')) {
                    q.push_back(tmp);
                    f[tmp.x][tmp.y][tmp.o] = f[q[n].x][q[n].y][q[n].o] + 1;
                    if ((tmp.x == en.x) && (tmp.y == en.y)) break;
                }
            }

            if ((q[n].y != 0) && (q[n].o != 7) && (q[n].o != 1) && (q[n].o != 5)) {
                tmp.x = q[n].x;
                tmp.y = q[n].y - 1;
                if (q[n].o == 3) tmp.o = 7; else tmp.o = 3;
                if ((f[tmp.x][tmp.y][tmp.o] == -1) && (m[tmp.x][tmp.y] != 'B')) {
                    q.push_back(tmp);
                    f[tmp.x][tmp.y][tmp.o] = f[q[n].x][q[n].y][q[n].o] + 1;
                    if ((tmp.x == en.x) && (tmp.y == en.y)) break;
                }
            }

            if ((q[n].y != b - 1) && (q[n].o != 5) && (q[n].o != 3) && (q[n].o  != 7)) {
                tmp.x = q[n].x;
                tmp.y = q[n].y + 1;
                if (q[n].o == 1) tmp.o = 5; else tmp.o = 1;
                if ((f[tmp.x][tmp.y][tmp.o] == -1) && (m[tmp.x][tmp.y] != 'B')) {
                    q.push_back(tmp);
                    f[tmp.x][tmp.y][tmp.o] = f[q[n].x][q[n].y][q[n].o] + 1;
                    if ((tmp.x == en.x) && (tmp.y == en.y)) break;
                }
            }
            
            n++;
        }
        
        if (n < q.size())
            cout << f[tmp.x][tmp.y][tmp.o] << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}
