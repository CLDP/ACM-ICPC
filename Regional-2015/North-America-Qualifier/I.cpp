#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;


int main() {
    int N;
    cin >> N;
    string Q;
    for (int i = 0; i < N; ++i) {
        getline(cin, Q);
        if (Q.substr(0, 10) == "Simon says") cout << Q.substr(10) << endl;
    }
    return 0;
}
