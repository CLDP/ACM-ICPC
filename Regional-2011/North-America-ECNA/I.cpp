#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

bool cross(int a, int b, int c, int d, int e, int f, int g, int h) {
    int p, q;
    p = (e-a)*(d-b)-(f-b)*(c-a);
    q = (g-a)*(d-b)-(h-b)*(c-a);
    if (p == 0 || q == 0) return false;
    if (p > 0 && q > 0) return false;
    if (p < 0 && q < 0) return false;
    p = (a-e)*(h-f)-(b-f)*(g-e);
    q = (c-e)*(h-f)-(d-f)*(g-e);
    if (p == 0 || q == 0) return false;
    if (p > 0 && q > 0) return false;
    if (p < 0 && q < 0) return false;
    return true;
}


int main() {
    int a, b, c, d, e, f, g, h, nn = 0;
    cin >> a >> b >> c >> d;
    while (a != 0 || b != 0 || c != 0 || d != 0) {
        ++nn;
        cin >> e >> f >> g >> h;
        double len, len2;
        if (cross(e, f, g, h, a, b, c, d)) {
            len = sqrt((a-e)*(a-e)+(b-f)*(b-f)) + sqrt((c-e)*(c-e)+(d-f)*(d-f));
            len2 = sqrt((a-g)*(a-g)+(b-h)*(b-h)) + sqrt((c-g)*(c-g)+(d-h)*(d-h));
            if (len2 < len) len = len2;
        } else {
            len = sqrt((a-c)*(a-c)+(b-d)*(b-d));
        }
        len  = len / 2;
        printf("Case %d: %.3lf\n",nn, len);
        cin >> a >> b >> c >> d;
    }

    return 0;
}
