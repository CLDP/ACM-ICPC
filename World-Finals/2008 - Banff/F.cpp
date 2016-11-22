#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

long long cal(long long N) {
    return N * (N - 1) * (N - 2) * (N - 3) / 24;
}

int main(){
    int times = 0;
    long long N;
    while (cin >> N) {
        if (N == 0) break;
        if (N & 1) 
            cout << "Case " << ++times << ": 0" << endl;
        else {
            N = (N + 4) >> 1;
            cout << "Case " << ++times << ": " << cal(N) + cal(N - 1)  << endl;
        }
    }
    return 0;
}
