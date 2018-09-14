#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

int base(char c) {
    if ('0' <= c && c <= '9') return c - '0' + 1;
    return c - 'a' + 11;
}

long long numB(string P, int b) {
    long long ans = 0;
    for (int i = 0; i < P.size(); ++i) {
        ans = ans * b + base(P[i]) - 1;
    }
    return ans;
}

char chr(int b) {
    if (b < 10) return b + '0';
    if (b == 36) return '0';
    return b - 10 + 'a';
}

bool all1(string Q) {
    for (int i = 0; i < Q.size(); ++i) {
        if (Q[i] != '1') return false;
    }
    return true;
}

bool check(int base, long long A, long long B, long long C, string op) {
    if (op == "+" && A + B == C) {
        cout << chr(base);
        return true;
    }
    if (op == "-" && A - B == C) {
        cout << chr(base);
        return true;
    }
    if (op == "*" && A * B == C) {
        cout << chr(base);
        return true;
    }
    if (op == "/" && C * B == A) {
        cout << chr(base);
        return true;
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    string P, op, Q, t, R;
    for (int i = 0; i < N; ++i) {
        cin >> P >> op >> Q >> t >> R;
        int b = 2;
        for (int j = 0; j < P.size(); ++j) b = max(b, base(P[j]));
        for (int j = 0; j < Q.size(); ++j) b = max(b, base(Q[j]));
        for (int j = 0; j < R.size(); ++j) b = max(b, base(R[j]));
        bool flag = false;
        if (all1(P) && all1(Q) && all1(R)) {
            int A = P.size(), B = Q.size(), C = R.size();
            flag |= check(1, A, B, C, op);
        }
        for (int j = b; j <= 36; ++j) {
            long long A = numB(P, j);
            long long B = numB(Q, j);
            long long C = numB(R, j);
            flag |= check(j, A, B, C, op);
        }
        if (!flag) cout << "invalid";
        cout << endl;
    }
    return 0;
}
