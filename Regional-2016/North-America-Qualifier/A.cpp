#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const string X[26] = {"@", "8", "(", "|)", "3", "#", "6",
                      "[-]", "|", "_|", "|<", "1", "[]\\/[]", "[]\\[]",
                      "0", "|D", "(,)", "|Z", "$", "']['",
                      "|_|", "\\/", "\\/\\/", "}{", "`/", "2"};

int main() {
    string P, Q;
    getline(cin, P);
    for (int i = 0; i < P.size(); ++i) {
        if (!isalpha(P[i])) {
            Q = Q + P[i];
            continue;
        }
        P[i] = tolower(P[i]);
        Q = Q + X[P[i] - 'a'];
    }
    cout << Q << endl;
    
    return 0;
}
