#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 3000000;
const int INF = 1000000000;

struct mirror {
    int a, b, k;
};

class compareX {
public:
    bool operator() (const mirror &A, const mirror &B) {
        if (A.a != B.a) return A.a < B.a;
        return A.b < B.b;
    }
};

class compareY {
public:
    bool operator() (const mirror &A, const mirror &B) {
        if (A.b != B.b) return A.b < B.b;
        return A.a < B.a;
    }
};

struct segment {
    int a, b, c;
    
    segment(int a1, int b1, int c1): a(a1), b(b1), c(c1) {}
    
    bool operator < (segment const &B) const {
        return c < B.c;
    }
};

struct event {
    int a, in;
    
    event(int a1, int in1): a(a1), in(in1) {}
    
    bool operator < (event const &B) const {
        if (a != B.a) return a < B.a;
        if (in > 0 && B.in < 0) return true;
        return false;
    }
};


int nn, R, C, N, M;
int l[MAXN], r[MAXN], k[MAXN];
set<mirror, compareX> X;
set<mirror, compareY> Y;


int build(int a, int b) {
    int t = ++nn;
    if (a < b) {
        int mid = (a + b) >> 1;
        l[t] = nn + 1;
        build(a, mid);
        r[t] = nn + 1;
        build(mid + 1, b);
        k[t] = 0;
    } else {
        l[t] = r[t] = k[t] = 0;
    }
    return 0;
}

bool get_segment(vector<segment> &Ax, vector<segment> &Ay, mirror &now, int &dir) {
    while (true) {
        if (dir == 0) {
            set<mirror, compareY>::iterator iter = Y.find(now);
            
            if (iter == Y.begin() || (--iter)->b != now.b) {
                if (1 <= now.a - 1) Ay.push_back(segment(1, now.a - 1, now.b)); 
                break;
            } else {
                if (iter->a + 1 <= now.a - 1) Ay.push_back(segment(iter->a + 1, now.a - 1, now.b)); 
                if (iter->k == 0) dir = 1; else dir = 3;
                now = *iter;
            }
        } else 
        if (dir == 1) {
            set<mirror, compareX>::iterator iter = X.find(now);
            if (++iter == X.end() || iter->a != now.a) {
                if (now.b + 1 <= C) Ax.push_back(segment(now.b + 1, C, now.a));
                if (now.a == R) return true;
                break;
            } else {
                if (now.b + 1 <= iter->b - 1) Ax.push_back(segment(now.b + 1, iter->b - 1, now.a));
                if (iter->k == 0) dir = 0; else dir = 2;
                now = *iter;
            }
        } else 
        if (dir == 2) {
            set<mirror, compareY>::iterator iter = Y.find(now);
            
            if (++iter == Y.end() || iter->b != now.b) {
                if (now.a + 1 <= R) Ay.push_back(segment(now.a + 1, R, now.b)); 
                break;
            } else {
                if (now.a + 1 <= iter->a - 1) Ay.push_back(segment(now.a + 1, iter->a - 1, now.b)); 
                if (iter->k == 0) dir = 3; else dir = 1;
                now = *iter;
            }
        } else {
            set<mirror, compareX>::iterator iter = X.find(now);
            
            if (iter == X.begin() || (--iter)->a != now.a) {
                if (1 <= now.b - 1) Ax.push_back(segment(1, now.b - 1, now.a));
                break;
            } else {
                if (iter->b + 1 <= now.b - 1) Ax.push_back(segment(iter->b + 1, now.b - 1, now.a));
                if (iter->k == 0) dir = 2; else dir = 0;
                now = *iter;
            }
        }
    }
    return false;
}

int insert(int t, int a, int b, int c, int d) {
    if (c == a && d == a) {
        k[t] += b;
        return 0;
    }
    int mid = (c + d) >> 1;
    if (a <= mid) insert(l[t], a, b, c, mid); else insert(r[t], a, b, mid + 1, d);
    k[t] = k[l[t]] + k[r[t]];
    return 0;
}

int query(int t, int a, int b, int c, int d) {
    if (a <= c && d <= b) return k[t];
    int mid = (c + d) >> 1, ans = 0;
    if (a <= mid) ans += query(l[t], a, b, c, mid); 
    if (mid + 1 <= b) ans += query(r[t], a, b, mid + 1, d);
    return ans;
}

int leftmost(int t, int a, int b, int c, int d) {
    if (b < c || d < a) return INF;
    if (c == d) {
        if (k[t] > 0) return c; else return INF;
    }
    if (k[t] == 0) return INF;
    
    int mid = (c + d) >> 1;
    int temp = leftmost(l[t], a, b, c, mid);
    if (temp < INF) return temp;
    return leftmost(r[t], a, b, mid + 1, d);
}

int main() {
    int times = 0;
    while (cin >> R >> C >> M >> N) {
        ++times;
        X.clear();
        Y.clear();
        for (int i = 0; i < M; ++i) {
            mirror P;
            cin >> P.a >> P.b;
            P.k = 0;
            X.insert(P);
            Y.insert(P);
        }
        for (int i = 0; i < N; ++i) {
            mirror P;
            cin >> P.a >> P.b;
            P.k = 1;
            X.insert(P);
            Y.insert(P);
        }
        
        vector<segment> Ax, Ay, Bx, By;
        
        // dir = 0 up, 1 right, 2 down, 3 left
        int dir = 1;
        
        bool flag = false;
        if (X.empty() || X.begin()->a != 1) {
            Ax.push_back(segment(1, C, 1));
            if (R == 1) flag = true;
        } else {
            mirror now = *X.begin();
            Ax.push_back(segment(1, now.b - 1, 1));
            if (now.k == 0) dir = 0; else dir = 2;
            flag = get_segment(Ax, Ay, now, dir);
        }
        
        if (flag) {
            cout << "Case " << times << ": " << 0 << endl;
            continue;
        }
        
        if (X.empty() || (--X.end())->a != R) {
            Bx.push_back(segment(1, C, R));
        } else {
            mirror now = *(--X.end());
            Bx.push_back(segment(now.b + 1, C, R));
            if (now.k == 0) dir = 2; else dir = 0;
            get_segment(Bx, By, now, dir);
        }
        
        sort(Ax.begin(), Ax.end());
        sort(Ay.begin(), Ay.end());
        sort(Bx.begin(), Bx.end());
        sort(By.begin(), By.end());
        
        vector<event> E;
        for (int i = 0; i < Ay.size(); ++i) {
            E.push_back(event(Ay[i].a, Ay[i].c));
            E.push_back(event(Ay[i].b, -Ay[i].c));
        }
        
        sort(E.begin(), E.end());
        nn = 0;
        build(1, C);
        
        int i = 0, ansA = R + 1, ansB = C + 1;
        long long ans = 0;
        for (vector<event>::iterator iter = E.begin(); iter != E.end() && i != Bx.size(); ) {
            if (iter->in > 0) {
                if (iter->a <= Bx[i].c) {
                    insert(1, iter->in, 1, 1, C);
                    ++iter;
                    continue;
                }
            } else {
                if (iter->a < Bx[i].c) {
                    insert(1, -iter->in, -1, 1, C);
                    ++iter;
                    continue;
                }
            }
            
            int temp = query(1, Bx[i].a, Bx[i].b, 1, C);
            if (temp > 0 && Bx[i].c <= ansA) {
                if (Bx[i].c < ansA) {
                    ansA = Bx[i].c;
                    ansB = leftmost(1, Bx[i].a, Bx[i].b, 1, C);
                } else {
                    ansB = min(ansB, leftmost(1, Bx[i].a, Bx[i].b, 1, C));
                }
            }
            ans += temp;
            ++i;
        }
        
        E.clear();
        for (int i = 0; i < Ax.size(); ++i) {
            E.push_back(event(Ax[i].a, Ax[i].c));
            E.push_back(event(Ax[i].b, -Ax[i].c));
        }
        
        sort(E.begin(), E.end());
        nn = 0;
        build(1, R);
        
        i = 0;
        for (vector<event>::iterator iter = E.begin(); iter != E.end() && i != By.size(); ) {
            if (iter->in > 0) {
                if (iter->a <= By[i].c) {
                    insert(1, iter->in, 1, 1, R);
                    ++iter;
                    continue;
                }
            } else {
                if (iter->a < By[i].c) {
                    insert(1, -iter->in, -1, 1, R);
                    ++iter;
                    continue;
                }
            }
            int temp = query(1, By[i].a, By[i].b, 1, R);
            if (temp > 0) {
                int upper = leftmost(1, By[i].a, By[i].b, 1, R);
                
                if (upper < ansA) {
                    ansA = upper;
                    ansB = By[i].c;
                } else
                if (upper == ansA) {
                    ansB = min(ansB, By[i].c);
                }
            }
            ans += temp;
            ++i;
        }
        if (ans != 0) 
           cout << "Case " << times << ": " << ans << " " << ansA << " " << ansB << endl;
        else 
           cout << "Case " << times << ": impossible" << endl;
    }
    
    return 0;
}
