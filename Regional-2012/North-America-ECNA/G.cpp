#include <iostream>
#include <unordered_map>
using namespace std;

struct change {
    long long a, b;
};

change x[10][10];
unordered_map<string, int> C;
string CC[10];


long long gcd(long long a, long long b) {
    while (b > 0) {
        long long t = a % b;
        a = b;
        b = t;      
    }     
    return a;
}



int main() {
    int N, T = 0;
    while (cin >> N) {
        if (N == 0) break;

        for (int i = 0; i < 10; ++i)
         for (int j = 0; j < 10; ++j) {
             x[i][j].a = 0;
             x[i][j].b = 1;    
         }
        C.clear();
        int M = 0;
        for (int i = 0; i < N; ++i) {
            int a, b;
            string P, Q, R;
            cin >> a >> P >> R >> b >> Q;
            if (C.find(P) == C.end()) C[P] = M++;
            if (C.find(Q) == C.end()) C[Q] = M++;

            int c = C[P], d = C[Q];
            CC[c] = P;
            CC[d] = Q;
            x[c][d].a = a;
            x[c][d].b = b;
            x[d][c].a = b;
            x[d][c].b = a;
        }

        for (int k = 0; k < M; ++k)
         for (int i = 0; i < M; ++i)
          for (int j = 0; j < M; ++j)
           if (x[i][j].a == 0 && x[i][k].a != 0 && x[k][j].a != 0) {
               x[i][j].a = x[i][k].a * x[k][j].a;
               x[i][j].b = x[i][k].b * x[k][j].b;
               long long current_gcd = gcd(x[i][j].a, x[i][j].b);
               x[i][j].a /= current_gcd;
               x[i][j].b /= current_gcd;
           }
        
        int a;
        string P;
        cin >> a >> P;
        int b = C[P];
        
        double ans = 1e15;
        int ansP;
        for (int i = 0; i < M; ++i) 
         if (i != b && x[b][i].a > 0) {
             long long curr = a * x[b][i].b + x[b][i].a - 1;
             curr /= x[b][i].a;
             if (curr * x[b][i].a * 1.0 / x[b][i].b < ans && curr <= 100000) {
                 ans = curr * x[b][i].a * 1.0 / x[b][i].b;
                 ansP = i;
             }
         }
        
        cout << "Case " << ++T << ": " << (a * x[b][ansP].b + x[b][ansP].a - 1) / x[b][ansP].a << " " << CC[ansP] << endl;
    }
    
    return 0;    
}
