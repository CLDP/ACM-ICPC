CPoint bp;  // Used for GrahamScan, lowest point

bool PolarCmp(const CPoint &p1, const CPoint &p2) {
    int u = dcmp(cross(bp, p1, p2));
    return u > 0 || (u == 0 && dcmp(dissqr(bp, p1) - dissqr(bp, p2)) < 0);
}
int GrahamScan(CPoint ch[], int n, int &m) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int u = dcmp(ch[i].x - ch[k].x);
        int v = dcmp(ch[i].y - ch[k].y);
        if (v < 0 || (v == 0 && u < 0)) k = i;
    }
    bp = ch[k];
    sort(ch, ch + n, PolarCmp);
    n = unique(ch, ch + n, PointEqual) - ch;
    if (n <= 1) {
        m = n;
        return 0;
    }
    if (dcmp(cross(ch[0], ch[1], ch[n - 1])) == 0) {
        m = 2;
        ch[1] = ch[n - 1];
        return 0;
    }
    ch[n++] = ch[0];
    int i = 1;
    for (int j = 2; j < n; ++j) {
        while (i > 0 && dcmp(cross(ch[i - 1], ch[i], ch[j])) < 0) --i;
        ch[++i] = ch[j];
    }
    m = i;
    return 0; 
}
CPoint ch[MAXN];
int main() {
    int N = 0, M;
    while (cin >> ch[N].x >> ch[N].y) ++N;
    GrahamScan(ch, N, M);
    for (int i = 0; i < M; ++i) cout << ch[i].x << " " << ch[i].y << endl;
    return 0;
}
