// Define X before this
int dcmp(double a, double b) {
    if (fabs(a - b) < EPS) return 0;
    if (a > b) return 1; else return -1;
}
bool cmp(const CPoint &A, const CPoint &B) {
    return dcmp(A.x, B.x) < 0;
}
bool cmp2(const int &A, const int &B) {
    return dcmp(X[A].y, X[B].y) < 0;
}
double dis(CPoint A, CPoint B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
double search(int s, int t) {
    int mid = (s + t) / 2;
    double ans = 1e300, temp;
    if (s >= t) return ans;
    int k;
    for (k = mid; k >= s && !dcmp(X[k].x, X[mid].x); --k);  ans = search(s, k);
    for (k = mid; k <= t && !dcmp(X[k].x, X[mid].x); ++k);  temp = search(k, t);
    if (temp < ans) ans = temp;
    
    vector<int> Y;
    for (int i = mid; i >= s && dcmp(X[mid].x - X[i].x, ans) <= 0; --i) Y.push_back(i);
    for (int i = mid + 1; i <= t && dcmp(X[i].x - X[mid].x, ans) <= 0; ++i) Y.push_back(i); 
    
    sort(Y.begin(), Y.end(), cmp2);
    int M = Y.size();
    for (int i = 0; i < M; ++i) 
     for (int j = 1; j <= 10; ++j)
      if (i + j < M)
       ans = min(ans, dis(X[Y[i]], X[Y[i + j]]));
    
    return ans;
}
double solve(int N) {
    sort(X, X + N, cmp);
    return search(0, N - 1);
}
