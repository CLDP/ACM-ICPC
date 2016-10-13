// Crossing angle of P0P1 -> P0P2, in (-pi, pi]
double angle(CPoint p0, CPoint &p1, CPoint p2) {
    double cr = cross(p0, p1, p2);
    double dt = dot(p0, p1, p2);
    if (dcmp(cr) == 0) cr = 0;
    if (dcmp(dt) == 0) dt = 0;
    return atan2(cr, dt);
}
// p0 on p1p2
int PointOnLine(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0;
}
int PointOnSegment(CPoint p0, CPoint p1, CPoint p2) {
    return dcmp(cross(p0, p1, p2)) == 0 && dcmp(dot(p0, p1, p2)) <= 0;
}
// 1 -> cross,   0 -> parallel,  -1 -> overlap
int LineIntersection(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint &cp) {
    double u = cross(p1, p2, p3), v = cross(p2, p1, p4);
    if (dcmp(u + v)) {
        cp.x = (p3.x * v + p4.x * u) / (u + v);
        cp.y = (p3.y * v + p4.y * u) / (u + v);
        return 1;
    }
    if (dcmp(u)) return 0;
    if (dcmp(cross(p3, p4, p1))) return 0;
    return -1;
}
// 1 ->intersect, 0 -> not (include parallel), -1 -> parallel and overlap
int SegmentIntersection(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint &cp) {
    int ret = LineIntersection(p1, p2, p3, p4, cp);
    if (ret == 1) return dcmp(dot(cp, p1, p2)) <= 0 && dcmp(dot(cp, p3, p4)) <= 0;
    if (ret == -1 && (PointOnSegment(p1, p3, p4) || PointOnSegment(p2, p3, p4) 
                   || PointOnSegment(p3, p1, p2) || PointOnSegment(p4, p1, p2))) return -1;
    return 0;
}
// 0 -> not, 1 -> in, 2 -> boundary
int PointInPolygon(CPoint cp, CPoint p[], int n) {
    int wn = 0;
    p[n] = p[0];
    for (int i = 0; i < n; ++i) {
        if (PointOnSegment(cp, p[i], p[i + 1])) return 2;
        int k = dcmp(cross(p[i], p[i + 1], cp));
        int d1 = dcmp(p[i + 0].y - cp.y);
        int d2 = dcmp(p[i + 1].y - cp.y);
        if (k > 0 && d1 <= 0 && d2 > 0) ++wn;
        if (k < 0 && d2 <= 0 && d1 > 0) --wn;
    }
    return wn != 0;
}
// Signed distance, use abs()
double PointToLine(CPoint p0, CPoint p1, CPoint p2, CPoint &cp) {
    double d = dis(p1, p2), s = cross(p1, p2, p0) / d;
    cp.x = p0.x + s * (p2.y - p1.y) / d;
    cp.y = p0.y - s * (p2.x - p1.x) / d;
    return s;
}
// Triangle centers
void Circumcenter(CPoint A, CPoint B, CPoint C, CPoint &cp) {
    double a1 = B.x - A.x, b1 = B.y - A.y, c1 = (sqr(a1) + sqr(b1)) / 2;
    double a2 = C.x - A.x, b2 = C.y - A.y, c2 = (sqr(a2) + sqr(b2)) / 2;
    double d = a1 * b2 - a2 * b1;
    cp.x = A.x + (c1 * b2 - c2 * b1) / d;
    cp.y = A.y + (a1 * c2 - a2 * c1) / d;
}
double Incenter(CPoint A, CPoint B, CPoint C, CPoint &cp) {
    double a = dis(B, C), b = dis(C, A), c = dis(A, B), p = (a + b + c) / 2;
    double s = sqrt(p * (p - a) * (p - b) * (p - c)), r = s / p;
    cp.x = (a * A.x + b * B.x + c * C.x) / (a + b + c);
    cp.y = (a * A.y + b * B.y + c * C.y) / (a + b + c);
    return r;
}
void Orthocenter(CPoint A, CPoint B, CPoint C, CPoint &cp) {
    Circumcenter(A, B, C, cp);
    cp.x = A.x + B.x + C.x - 2 * cp.x;
    cp.y = A.y + B.y + C.y - 2 * cp.y;
}
// 012 intersect points
int CircleCrossLine(CPoint p0, double r, CPoint p1, CPoint p2, CPoint &cp1, CPoint &cp2) {
    double d = fabs(PointToLine(p0, p1, p2, cp1));
    if (dcmp(d - r) > 0) return 0;
    if (dcmp(d - r) == 0) { cp2 = cp1; return 1;}
    d = sqrt(r * r - d * d) / dis(p1, p2);
    double dx = (p2.x - p1.x) * d;
    double dy = (p2.y - p1.y) * d;
    cp2.x = cp1.x + dx; cp2.y = cp1.y + dy;
    cp1.x = cp1.x - dx; cp1.y = cp1.y - dy;
    return 2;
}
// 012 intersect points
int CircleCrossCircle(CPoint p1, double r1, CPoint p2, double r2, CPoint &cp1, CPoint &cp2) {
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (d + EPS < 0) return 0;
    if (d < EPS) d = 0; else d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d; sq *= 2;
    cp1.x = (x - dy) / sq; cp1.y = (y + dx) / sq;
    cp2.x = (x + dy) / sq; cp2.y = (y - dx) / sq;
    if (d > EPS) return 2;
    return 1;
}

