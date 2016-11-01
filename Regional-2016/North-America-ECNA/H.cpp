#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int N, M;
string A[MAXN], B[MAXN], X[MAXN];

bool inside(int a, int b) {
    return 0 <= a && a < N && 0 <= b && b < M;
}

int count(int a, int b) {
    int ans = 0;
    for (int i = 0; i < 4; ++i) {
        int c = a + MX[i];
        int d = b + MY[i];
        if (inside(c, d) && X[c][d] == 'X') ++ans;
    }
    return ans;
}

void dfsA(int a, int b) {
    if (X[a][b] == '.') return ;
    A[a][b] = 'X';
    for (int i = 0; i < 4; ++i) {
        int c = a + MX[i];
        int d = b + MY[i];
        while (inside(c, d) && A[c][d] == '.' && X[c][d] == 'X') {
            A[c][d] = 'X';
            c += MX[i];
            d += MY[i];
        }
        c -= MX[i];
        d -= MY[i];
        if ((c != a || d != b) && X[c][d] == 'X') dfsA(c, d);
    }
}


void dfsB(int a, int b) {
    if (X[a][b] == '.') return ;
    B[a][b] = 'X';
    for (int i = 0; i < 4; ++i) {
        int c = a + MX[i];
        int d = b + MY[i];
        while (inside(c, d) && B[c][d] == '.' && X[c][d] == 'X') {
            B[c][d] = 'X';
            c += MX[i];
            d += MY[i];
        }
        c -= MX[i];
        d -= MY[i];
        if ((c != a || d != b) && X[c][d] == 'X') dfsB(c, d);
    }
}



void dfsAA(int a, int b) {
    if (A[a][b] == 'X' || A[a][b] == 'Y') return ;
    A[a][b] = 'Y';
    for (int i = 0; i < 4; ++i) {
        int c = a + MX[i];
        int d = b + MY[i];
        if (inside(c, d) && A[c][d] == '.') dfsAA(c, d);
    }
}

void dfsBB(int a, int b) {
    if (B[a][b] == 'X' || B[a][b] == 'Y') return ;
    B[a][b] = 'Y';
    for (int i = 0; i < 4; ++i) {
        int c = a + MX[i];
        int d = b + MY[i];
        if (inside(c, d) && B[c][d] == '.') dfsBB(c, d);
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> X[i];
        A[i] = B[i] = string(M, '.');
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (X[i][j] == '.' || X[i][j] == 'X') continue;
            if (X[i][j] == 'A') {
                X[i][j] = 'X';
                dfsA(i, j);
            } else {
                X[i][j] = 'X';
                dfsB(i, j);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        dfsAA(i, 0);
        dfsAA(i, M - 1);
        dfsBB(i, 0);
        dfsBB(i, M - 1);
    }
    for (int i = 0; i < M; ++i) {
        dfsAA(0, i);
        dfsAA(N - 1, i);
        dfsBB(0, i);
        dfsBB(N - 1, i);
    }

    int AA, BB, CC;
    AA = BB = CC = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i][j] == '.') A[i][j] = 'A';
            if (B[i][j] == '.') B[i][j] = 'B';
            if (A[i][j] == 'A' && B[i][j] == 'Y') ++AA;
            if (B[i][j] == 'B' && A[i][j] == 'Y') ++BB;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i][j] == 'A' && B[i][j] == 'B') ++CC;
        }
    }
    cout << AA << " " << BB << " " << CC << endl;

    return 0;
}
