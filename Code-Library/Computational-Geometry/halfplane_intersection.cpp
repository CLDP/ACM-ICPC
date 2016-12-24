typedef CPoint Vector;

struct Line {
    // point on the line
    CPoint p;
    // direction
    Vector v;
    // angle from x+ to vector v
    double ang;
    Line() {}
    Line(CPoint p, Vector v): p(p), v(v) {ang = atan2(v.y, v.x);}
    bool operator < (const Line &L) const {
        return ang < L.ang;
    }
};
Vector operator + (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}
Vector operator - (CPoint A, CPoint B) {
    return Vector(A.x - B.x, A.y - B.y);
}
Vector operator * (Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}
Vector operator / (Vector A, double p) {
    return Vector(A.x / p, A.y / p);
}
double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}
bool OnLeft(Line L, CPoint P) {
    return Cross(L.v, P - L.p) > 0;
}
CPoint GetIntersection(Line a, Line b) {
    Vector u = a.p - b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v * t;
}

int HalfplaneIntersection(Line *L, int n, CPoint *poly) {
    sort(L, L + n);
    int first = 0, last = 0;
    CPoint *p = new CPoint[n];
    Line *q = new Line[n];
    q[0] = L[0];
    for (int i = 1; i < n; ++i) {
        while (first < last && !OnLeft(L[i], p[last - 1])) --last;
        while (first < last && !OnLeft(L[i], p[first])) ++first;
        q[++last] = L[i];
        if (fabs(Cross(q[last].v, q[last - 1].v)) < EPS) {
            // Two parallel lines, same direction
            --last;
            if (OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if (first < last) p[last - 1] = GetIntersection(q[last - 1], q[last]);
    }
    // Remove useless half planes
    while (first < last && !OnLeft(q[first], p[last - 1])) --last;
    // Need to add four boundary lines to make this correct
    // Or if you know the given region is bounded
    if (last - first <= 1) return 0; 
    p[last] = GetIntersection(q[last], q[first]);

    int m = 0;
    for (int i = first; i <= last; ++i) poly[m++] = p[i];
    delete[] p;
    delete[] q;
    return m;
}

double PolygonArea(CPoint *p, int n) {
    double area = 0;
    for (int i = 1; i < n - 1; ++i) area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return fabs(area) / 2;
}

double Length(Vector A) {
    return sqrt(A.x * A.x + A.y * A.y);
}

// Unit normal vector
Vector Normal(Vector A) {
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}

// Move the line inward for distance d
Line MoveLine(Line l, double d) {
    return Line(l.p + Normal(l.v) * d, l.v);
}
