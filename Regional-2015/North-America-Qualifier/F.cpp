#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

bool z[26];

int main() {
    int N;
    string P;
    cin >> N;
    getline(cin, P);
    for (int i = 1; i <= N; ++i) {
        getline(cin, P);
        memset(z, 0, sizeof(z));
        for (int j = 0; j < P.size(); ++j) {
            if (!isalpha(P[j])) continue;
            z[tolower(P[j]) - 'a'] = true;
        }
        bool flag = true;
        for (int j = 0; j < 26; ++j) flag &= z[j];
        if (flag) {
            cout << "pangram" << endl;
        } else {
            cout << "missing ";
            for (int i = 0; i < 26; ++i) 
             if (!z[i]) cout << (char)('a' + i);
            cout << endl;
        }
    }
    return 0;
}
