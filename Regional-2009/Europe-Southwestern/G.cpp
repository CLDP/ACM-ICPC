#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct node {
    double x1, x2, y;
};

double f[1005][2];

    
int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        
        vector<node> t;
        node temp;
        cin >> temp.x1 >> temp.y;
        temp.x2 = temp.x1;
        t.push_back(temp);
        double best = 0;
        
        for (int i = 0; i < N; ++i) {
            cin >> temp.y >> temp.x1 >> temp.x2;
            t.push_back(temp);
        }
        
        for (int i = 0; i <= N; ++i) {
            f[i][0] = 0;
            f[i][1] = 0;
        }
        
        for (int i = 0; i <= N; ++i) {
            bool sat = true;
            double lx = t[i+1].x1 - t[i].x1;
            double ly = t[i].y - t[i+1].y;
            double rx = t[i+1].x2 - t[i].x1;
            double ry = t[i].y - t[i+1].y;
            for (int j = i + 1; j <= N; ++j) {
                double tx = t[j].x1 - t[i].x1;
                double ty = t[i].y - t[j].y;
                if ((tx * ly >= ty * lx) && (rx * ty >= tx * ry)) {
                    double tmp = sqrt((double)(t[j].x1 - t[i].x1) * (t[j].x1 - t[i].x1) 
                                            + (t[j].y - t[i].y) * (t[j].y - t[i].y));                
                    if ((f[j][0] == 0) || (f[i][0] + tmp < f[j][0])) f[j][0] = f[i][0] + tmp;
                }
                if (tx * ly >= ty * lx) {
                    lx = tx;
                    ly = ty;
                }
                
                tx = t[j].x2 - t[i].x1;
                ty = t[i].y - t[j].y;
                if ((tx * ly >= ty * lx) && (rx * ty >= tx * ry)) {
                    double tmp = sqrt((double)(t[j].x2 - t[i].x1) * (t[j].x2 - t[i].x1) 
                                            + (t[j].y - t[i].y) * (t[j].y - t[i].y));                
                    if ((f[j][1] == 0) || (f[i][0] + tmp < f[j][1])) f[j][1] = f[i][0] + tmp;
                }
                if (rx * ty >= tx * ry) {
                    rx = tx;
                    ry = ty;
                }
                
                if (lx * ry > rx * ly) {
                    sat = false;
                    break;
                }
            }
            if (sat) {
                double tmp;
                if ((lx <= 0) && (rx >= 0)) 
                    tmp = t[i].y - t[N].y;
                else 
                if (rx < 0) {
                    tmp = sqrt((double)(rx * rx + ry * ry)) * (t[i].y - t[N].y) / ry;
                } else {
                    tmp = sqrt((double)(lx * lx + ly * ly)) * (t[i].y - t[N].y) / ly;
                }
                if ((best == 0) || (f[i][0] + tmp < best)) best = f[i][0] + tmp; 
            }

            sat = true;
            lx = t[i+1].x1 - t[i].x2;
            ly = t[i].y - t[i+1].y;
            rx = t[i+1].x2 - t[i].x2;
            ry = t[i].y - t[i+1].y;
            for (int j = i + 1; j <= N; ++j) {
                double tx = t[j].x1 - t[i].x2;
                double ty = t[i].y - t[j].y;
                if ((tx * ly >= ty * lx) && (rx * ty >= tx * ry)) {
                    double tmp = sqrt((double)(t[j].x1 - t[i].x2) * (t[j].x1 - t[i].x2) 
                                            + (t[j].y - t[i].y) * (t[j].y - t[i].y));                
                    if ((f[j][0] == 0) || (f[i][1] + tmp < f[j][0])) f[j][0] = f[i][1] + tmp;
                }
                if (tx * ly > ty * lx) {
                    lx = tx;
                    ly = ty;
                }
                
                tx = t[j].x2 - t[i].x2;
                ty = t[i].y - t[j].y;
                if ((tx * ly >= ty * lx) && (rx * ty >= tx * ry)) {
                    double tmp = sqrt((double)(t[j].x2 - t[i].x2) * (t[j].x2 - t[i].x2) 
                                            + (t[j].y - t[i].y) * (t[j].y - t[i].y));                
                    if ((f[j][1] == 0) || (f[i][1] + tmp < f[j][1])) f[j][1] = f[i][1] + tmp;
                }
                if (rx * ty >= tx * ry) {
                    rx = tx;
                    ry = ty;
                }
                
                if (lx * ry > rx * ly) {
                    sat = false;
                    break;
                }
            }
            if (sat) {
                double tmp;
                if ((lx <= 0) && (rx >= 0))
                    tmp = t[i].y - t[N].y;
                else 
                if (rx < 0) {
                    tmp = sqrt((double)(rx * rx + ry * ry)) * (t[i].y - t[N].y) / ry;
                } else {
                    tmp = sqrt((double)(lx * lx + ly * ly)) * (t[i].y - t[N].y) / ly;
                }
                if ((best == 0) || (f[i][1] + tmp < best)) best = f[i][1] + tmp;
            }
        }
        
        printf("%.9f\n", best);
    }

    return 0;
}
