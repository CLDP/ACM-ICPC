#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int INF = 2000000000;

struct box {
    int x, y, w, h;
    box() {}
    box(int _x, int _y, int _w, int _h) :
        x(_x), y(_y), w(_w), h(_h) {}
};

struct boundary {
    int a, b, c, ID;
    boundary() {}
    boundary(int _a, int _b, int _c, int _ID = -1) :
        a(_a), b(_b), c(_c), ID(_ID) {}
};

bool inside(int a, int b, box B) {
    return B.x <= a && a < B.x + B.w && B.y <= b && b < B.y + B.h;
}

bool cross(box A, box B) {
    if (max(A.x, B.x) >= min(A.x + A.w, B.x + B.w)) return false;
    if (max(A.y, B.y) >= min(A.y + A.h, B.y + B.h)) return false;
    return true;
}

bool inseg(int a, int b, int c, int d) {
    if (a <= c && c < b) return true;
    if (a < d && d <= b) return true;
    if (c <= a && a < d) return true;
    if (c < b && b <= d) return true;
    return false;
}

int find_time(vector<boundary> &Y, boundary X) {
    int T = INF;
    for (int i = 0; i < Y.size(); ++i) {
        if (!inseg(Y[i].a, Y[i].b, X.a, X.b)) continue;
        if (X.c >= Y[i].c) T = min(T, X.c - Y[i].c);
    }
    return T;
}

int solve(vector<box> &X, int w, int j, int W, int times) {
    int w_org = w;
    vector<boundary> Y;
    vector<bool> Z(X.size(), false);
    Z[j] = true;

    int move = 0;
    Y.push_back(boundary(X[j].y, X[j].y + X[j].h, X[j].x + X[j].w, j));
    int A = X[j].y, B = X[j].y + X[j].h, C = X[j].x + X[j].w;

    while (w > 0) {
        int minT = INF;
        vector<int> T(X.size(), INF);
        for (int i = 0; i < X.size(); ++i) {
            if (Z[i]) continue;
            if (inseg(X[i].y, X[i].y + X[i].h, A, B)) {
                T[i] = find_time(Y, boundary(X[i].y, X[i].y + X[i].h, X[i].x));
                minT = min(minT, T[i]);
            }
        }

        minT = min(minT, w);
        bool flag = false;
        if (minT > W - C) {
            flag = true;
            minT = min(minT, W - C);
        }
        w -= minT;
        C += minT;

        for (int i = 0; i < Y.size(); ++i) Y[i].c += minT;
        for (int i = 0; i < X.size(); ++i) {
            if (T[i] != minT) continue;
            Y.push_back(boundary(X[i].y, X[i].y + X[i].h, X[i].x + X[i].w, i));
            A = min(A, X[i].y);
            B = max(B, X[i].y + X[i].h);
            C = max(C, X[i].x + X[i].w);
            Z[i] = true;
        }
        move += minT;
        if (flag) break;
    }
    for (int i = 0; i < Y.size(); ++i) X[Y[i].ID].x = Y[i].c - X[Y[i].ID].w;
    if (move != w_org) {
        cout << "Command " << times << ": MOVE - moved " << move << " instead of " << w_org << endl;
    }
    return 0;
}

vector<box> X;

int main() {
    int W, H, times = 0;
    cin >> W >> H;
    string command;
    while (cin >> command) {
        ++times;
        if (command == "OPEN") {
            int x, y, w, h;
            cin >> x >> y >> w >> h;
            box M(x, y, w, h);
            bool flag = true;
            if (x + w > W || y + h > H) flag = false;
            for (int i = 0; i < X.size(); ++i) {
                if (cross(X[i], M)) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                X.push_back(M);
            } else {
                cout << "Command " << times << ": OPEN - window does not fit" << endl;
            }
            continue;
        }
        if (command == "CLOSE") {
            int x, y;
            cin >> x >> y;
            bool flag = false;
            for (int i = 0; i < X.size(); ++i) {
                if (inside(x, y, X[i])) {
                    flag = true;
                    X.erase(X.begin() + i);
                    break;
                }
            }
            if (!flag) {
                cout << "Command " << times << ": CLOSE - no window at given position" << endl;
            }
            continue;
        }
        if (command == "RESIZE") {
            int x, y, w, h;
            cin >> x >> y >> w >> h;
            int j = -1;
            for (int i = 0; i < X.size(); ++i) {
                if (inside(x, y, X[i])) {
                    j = i;
                    break;
                }
            }
            if (j == -1) {
                cout << "Command " << times << ": RESIZE - no window at given position" << endl;
                continue;
            }
            box M(X[j].x, X[j].y, w, h);
            if (M.x + M.w > W || M.y + M.h > H) j = -1;
            for (int i = 0; i < X.size(); ++i) {
                if (i == j) continue;
                if (cross(M, X[i])) {
                    j = -1;
                    break;
                }
            }
            if (j == -1) {
                cout << "Command " << times << ": RESIZE - window does not fit" << endl;
                continue;
            }
            X[j] = M;
            continue;
        }
        if (command == "MOVE") {
            int x, y, w, h;
            cin >> x >> y >> w >> h;
            int j = -1;
            for (int i = 0; i < X.size(); ++i) {
                if (inside(x, y, X[i])) {
                    j = i;
                    break;
                }
            }
            if (j == -1) {
                cout << "Command " << times << ": MOVE - no window at given position" << endl;
                continue;
            }

            if (h == 0 && w == 0) continue;

            if (w > 0) {
                solve(X, w, j, W, times);
                continue;
            } 
            if (w < 0) {
                for (int i = 0; i < X.size(); ++i) X[i].x = W - X[i].x - X[i].w;
                solve(X, -w, j, W, times);
                for (int i = 0; i < X.size(); ++i) X[i].x = W - X[i].x - X[i].w;
                continue;
            }
            if (h > 0) {
                for (int i = 0; i < X.size(); ++i) {
                    swap(X[i].x, X[i].y);
                    swap(X[i].w, X[i].h);
                }
                solve(X, h, j, H, times);
                for (int i = 0; i < X.size(); ++i) {
                    swap(X[i].x, X[i].y);
                    swap(X[i].w, X[i].h);
                }
                continue;
            }
            if (h < 0) {
                for (int i = 0; i < X.size(); ++i) {
                    swap(X[i].x, X[i].y);
                    swap(X[i].w, X[i].h);
                }
                for (int i = 0; i < X.size(); ++i) X[i].x = H - X[i].x - X[i].w;
                solve(X, -h, j, H, times);
                for (int i = 0; i < X.size(); ++i) X[i].x = H - X[i].x - X[i].w;
                for (int i = 0; i < X.size(); ++i) {
                    swap(X[i].x, X[i].y);
                    swap(X[i].w, X[i].h);
                }
                continue;
            }
        }
    }

    cout << X.size() << " window(s):" << endl;
    for (int i = 0; i < X.size(); ++i) {
        cout << X[i].x << " " << X[i].y << " " << X[i].w << " " << X[i].h << endl;
    }

    return 0;
}
