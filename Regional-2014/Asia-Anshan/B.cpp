#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct girl {
    int u;
    long long c;
};

girl X[5010];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M = 0;
        int TOP = -1;
        cin >> N;
        string P;
        for (int i = 1; i <= N; ++i) {
            cin >> P;
            cout << "Operation #" << i << ": ";
            
            if (P == "Add") {
                int U;
                cin >> U;
                bool same = false;
                for (int j = 0; j < M; ++j) {
                    if (X[j].u == U) {
                        same = true;
                        break;
                    }
                }
                if (same) {
                    cout << "same priority." << endl;
                } else {
                    cout << "success." << endl;
                    X[M].u = U;
                    X[M].c = 0;
                    ++M;
                }
            } else
            if (P == "Close") {
                int U;
                cin >> U;
                bool same = false;
                for (int j = 0; j < M; ++j) {
                    if (X[j].u == U) {
                        cout << "close " << X[j].u << " with " << X[j].c << "." << endl;
                        if (TOP == j) TOP = -1;
                        
                        same = true;
                        for (int k = j + 1; k < M; ++k) X[k - 1] = X[k];
                        if (TOP > j) --TOP;
                        --M;
                        
                        break;
                    }
                }
                if (!same) {
                    cout << "invalid priority." << endl;
                }
            } else
            if (P == "Chat") {
                int U;
                cin >> U;
                if (M > 0) {
                    if (TOP != -1) {
                        X[TOP].c += U;
                        cout << "success." << endl;
                    } else {
                        X[0].c += U;
                        cout << "success." << endl;
                    }
                } else {
                    cout << "empty." << endl;
                }
            } else
            if (P == "Rotate") {
                int U;
                cin >> U;
                if (U <= M && U >= 1) {
                    --U;
                    if (TOP == U) {
                        TOP = 0;
                    } else 
                    if (TOP < U && TOP != -1) {
                        ++TOP;
                    }
                    girl temp = X[U];
                    for (int j = U; j > 0; --j) X[j] = X[j - 1];
                    X[0] = temp;
                    cout << "success." << endl;
                } else {
                    cout << "out of range." << endl;
                }
            } else
            if (P == "Prior") {
                if (M == 0) {
                    cout << "empty." << endl;
                } else {
                    int i = 0;
                    for (int j = 1; j < M; ++j)
                     if (X[j].u > X[i].u) i = j;
                    if (TOP == i) {
                        TOP = 0;
                    } else
                    if (TOP < i && TOP != -1) {
                        ++TOP;
                    }
                    
                    girl temp = X[i];
                    for (int j = i; j > 0; --j) X[j] = X[j - 1];
                    X[0] = temp;
                    cout << "success." << endl;
                }
            } else
            if (P == "Choose") {
                int U;
                cin >> U;
                bool same = false;
                for (int i = 0; i < M; ++i) {
                    if (X[i].u == U) {
                        same = true;
                        if (TOP == i) {
                            TOP = 0;
                        } else 
                        if (TOP < i && TOP != -1) {
                            ++TOP;
                        }
                        
                        girl temp = X[i];
                        for (int j = i; j > 0; --j) X[j] = X[j - 1];
                        X[0] = temp;
                        cout << "success." << endl;
                        break;
                    }
                }
                
                if (!same) {
                    cout << "invalid priority." << endl;
                }
            } else 
            if (P == "Top") {
                int U;
                cin >> U;
                bool same = false;
                for (int i = 0; i < M; ++i) {
                    if (X[i].u == U) {
                        same = true;
                        TOP = i;
                        cout << "success." << endl;
                        break;
                    }
                }
                
                if (!same) {
                    cout << "invalid priority." << endl;
                }
            } else 
            if (P == "Untop") {
                if (TOP != -1) {
                    TOP = -1;
                    cout << "success." << endl;
                } else {
                    cout << "no such person." << endl;
                }
            }
            
        }
        
        if (TOP != -1 && X[TOP].c != 0) {
            cout << "Bye " << X[TOP].u << ": " << X[TOP].c << endl;
            X[TOP].c = 0;
        }
        for (int i = 0; i < M; ++i) {
            if (X[i].c > 0)
                cout << "Bye " << X[i].u << ": " << X[i].c << endl;
        }
    }
    return 0;
}
