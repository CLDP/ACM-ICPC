#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int MAXN = 30;
unordered_map<string, int> C;

int MM;
long long V[MAXN][MAXN];

int getnum(string P, int &b) {
    int a = 0;
    while (b < P.size() && P[b] >= '0' && P[b] <= '9') {
        a = a * 10 + P[b] - '0';
        ++b;
    }
    return a;
}

void add(string Q, int a, int c) {
    if (C.find(Q) == C.end()) C[Q] = MM++;
    int d = C[Q];
    V[a][d] += c;
}

void splitit(string P, int a, int KM) {
    if (P.size() == 0) return ;

    if (P[0] >= 'A' && P[0] <= 'Z') {
        string Q = P.substr(0, 1);
        if (P[1] >= 'a' && P[1] <= 'z') {
            Q = Q + P[1];
            if (P.size() > 2 && P[2] >= '0' && P[2] <= '9') {
                int b = 2;
                int c = getnum(P, b);
                add(Q, a, c * KM);
                splitit(P.substr(b, P.size()), a, KM);
            } else {
                add(Q, a, KM);
                splitit(P.substr(2, P.size()), a, KM);
            }
        } else 
        if (P[1] >= '1' && P[1] <= '9') {
            int b = 1;
            int c = getnum(P, b);
            add(Q, a, c * KM);
            splitit(P.substr(b, P.size()), a, KM);
        } else {
            add(Q, a, KM);
            splitit(P.substr(1, P.size()), a, KM);
        }
    } else {
        int n = 1, b = 0;
        while (n > 0) {
            ++b;
            if (P[b] == '(') ++n; 
            if (P[b] == ')') --n;
        }
        int L = b - 1;
        ++b;
        int c = getnum(P, b);
        splitit(P.substr(1, L), a, KM * c);
        splitit(P.substr(b, P.size()), a, KM);
    }
}


long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

class HP {
public:
    long long a, b;

    HP(): a(0), b(1) {}
    HP(long long _a, long long _b): a(_a), b(_b) {}

    HP operator + (const HP &B) {
        HP C;
        C.b = lcm(b, B.b);
        C.a = a * C.b / b + B.a * C.b / B.b;
        long long ll = gcd(abs(C.a), C.b);
        C.a /= ll;
        C.b /= ll;
        return C;
    }

    HP operator - (const HP &B) {
        HP C;
        C.b = lcm(b, B.b);
        C.a = a * C.b / b - B.a * C.b / B.b;
        long long ll = gcd(abs(C.a), C.b);
        C.a /= ll;
        C.b /= ll;
        return C;
    }

    HP operator * (const int &B) {
        HP C = *this;
        C.a *= B;
        long long ll = gcd(abs(C.a), C.b);
        C.a /= ll;
        C.b /= ll;
        return C;
    }
};

long long A[MAXN][MAXN];
long long sol[MAXN];

void clear(int a, int L) {
    long long S = 0;
    for (int p = 0; p < L; ++p) {
        if (A[a][p] == 0) continue;
        if (S == 0) S = abs(A[a][p]); else S = gcd(S, abs(A[a][p]));
    }
    if (S > 0) {
        for (int p = 0; p < L; ++p) A[a][p] /= S;
    }
}

int print(int N, int M) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) cout << A[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    return 0;
}

int Gauss(int equ, int var) {
    for (int i = 0; i < equ; ++i) clear(i, var);

    int i = 0, l = 0;
    while (i < var && l < equ) {
        long long k = 0;
        int t = 0;
        for (int j = l; j < equ; ++j) {
            if (abs(A[j][i]) < k) continue;
            k = abs(A[j][i]);
            t = j;
        }
        if (k == 0) {
            ++i;
            continue;
        } 
        for (int p = i; p < var; ++p) swap(A[l][p], A[t][p]);
        if (A[l][i] < 0) for (int p = i; p < var; ++p) A[l][p] = -A[l][p];
        clear(l, var);
        k = A[l][i];

        for (int j = l + 1; j < equ; ++j) {
            if (A[j][i] == 0) continue;
            long long S = lcm(k, abs(A[j][i]));
            long long t1 = S / k;
            long long t2 = S / A[j][i];
            for (int p = i; p < var; ++p) A[j][p] = A[j][p] * t2 - A[l][p] * t1;
            clear(j, var);
        }
        ++i;
        ++l;
    }
    while (equ > 0) {
        bool flag = true;
        for (int p = 0; p < var; ++p) flag &= (A[equ - 1][p] == 0);
        if (flag) --equ; else break;
    }

    int pos = 0, neg = 0;
    long long C1 = 0, C2 = 0;
    --equ;
    for (int i = 0; i < var; ++i) {
        if (A[equ][i] > 0) {
            ++pos;
            C1 = A[equ][i];
        }
        if (A[equ][i] < 0) {
            ++neg;
            C2 = A[equ][i];
        }
    }

    if (pos != 1 || neg != 1) return -1;

    HP X[MAXN];
    bool Z[MAXN];
    memset(Z, 0, sizeof(Z));

    for (int i = 0; i < var; ++i) {
        X[i] = HP();

        if (A[equ][i] > 0) {
            Z[i] = true;
            X[i].a = 1;
        }
        if (A[equ][i] < 0) {
            Z[i] = true;
            X[i].a = C1;
            X[i].b = -C2;
        }
    }

    while (equ > 0) {
        --equ;
        pos = 0;
        int j = -1;
        for (int i = 0; i < var; ++i) {
            if (Z[i] || A[equ][i] == 0) continue;
            ++pos;
            j = i;
        }
        if (pos > 1) return -1;
        if (j == -1) cout << "ERRORR!!!" << endl;
        Z[j] = true;
        for (int i = 0; i < var; ++i) {
            if (A[equ][i] == 0) continue;
            X[j] = X[j] - X[i] * A[equ][i];
        }
        X[j].b *= abs(A[equ][j]);
        if (A[equ][j] < 0) X[j].a = -X[j].a;
        if (X[j].a < 0) return -1;
    }

    long long dm = 1;
    for (int i = 0; i < var; ++i) dm = lcm(dm, X[i].b);
    for (int i = 0; i < var; ++i) sol[i] = X[i].a * dm / X[i].b;
    dm = sol[0];
    for (int i = 0; i < var; ++i) dm = gcd(dm, sol[i]);
    for (int i = 0; i < var; ++i) sol[i] /= dm;

    return 0;
}

int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N + M == 0) break;
        ++times;
        MM = 0;
        memset(A, 0, sizeof(A));
        memset(V, 0, sizeof(V));

        C.clear();

        for (int i = 0; i < N; ++i) {
            string P;
            cin >> P;
            splitit(P, i, 1);
        }
        for (int i = 0; i < M; ++i) {
            string P;
            cin >> P;
            splitit(P, i + N, 1);
        }
        for (int i = 0; i < MM; ++i) {
            for (int j = 0; j < N; ++j) A[i][j] = V[j][i];
            for (int j = 0; j < M; ++j) A[i][j + N] = -V[j + N][i];
        }

        cout << "Case " << times << ":";
        if (Gauss(MM, N + M) == -1) {
            cout << " No" << endl;
        } else {   
            for (int i = 0; i < N + M; ++i) cout << " " << sol[i];
            cout << endl;
        }

    }
    return 0;
}
