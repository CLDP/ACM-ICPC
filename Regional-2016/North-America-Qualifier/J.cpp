#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    string P;
    getline(cin, P);
    for (int i = 0; i < N; ++i) {
        getline(cin, P);   
        cout << P.size() << endl;
    }
    return 0;
}
