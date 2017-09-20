typedef long long ll;
struct Point {
    ll x, y;
};
struct Line {
    Point p1, p2;
};

// Note that Lines are either vertical or horizontal and variable type is NOT reference
ll get_dist(Line l, Line r) { 
    if (l.p1.x > l.p2.x) swap(l.p1, l.p2);
    if (l.p1.y > l.p2.y) swap(l.p1, l.p2);
    if (r.p1.x > r.p2.x) swap(r.p1, r.p2);
    if (r.p1.y > r.p2.y) swap(r.p1, r.p2);
    if (r.p1.x == r.p2.x) swap(l, r);
    const ll INF = 1e15;
    ll res = INF;
    if (l.p1.y == l.p2.y) {
        assert(r.p1.y == r.p2.y);
        if (!(l.p2.x < r.p1.x ||  r.p2.x < l.p1.x)) res = min(res, abs(l.p1.y - r.p1.y));
    }
    else if (r.p1.x == r.p2.x) {
        assert(l.p1.x == l.p2.x);
        if (!(l.p2.y < r.p1.y || r.p2.y < l.p1.y)) res = min(res, abs(l.p1.x - r.p1.x));
    }
    else {
        assert(l.p1.x == l.p2.x && r.p1.y == r.p2.y);
        if (r.p1.x <= l.p1.x && l.p1.x <= r.p2.x) res = min({res, abs(r.p1.y - l.p1.y), abs(r.p1.y - l.p2.y)});
        if (l.p1.y <= r.p1.y && r.p1.y <= l.p2.y) res = min({res, abs(l.p1.x - r.p1.x), abs(l.p2.x - r.p1.x)});
        if (r.p1.x <= l.p1.x && l.p1.x <= r.p2.x &&
                                l.p1.y <= r.p1.y && r.p1.y <= l.p2.y) res = 0;
    }
    if (res < INF) res = res * res;
    for (auto &i : {l.p1, l.p2})
        for (auto &j : {r.p1, r.p2})
            res = min(res, (i.x - j.x) * (i.x - j.x) + (i.y-j.y) * (i.y-j.y));
    return res;
}



ll cross(const Point &O, const Point &A, const Point &B){
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// param:: vector of Point with x,y coordinates in long long int, P.size >= 3
// return:: convex_hull with x, y coordinates in long long int
// the first and the last element is SAME
typedef long long ll;
vector<Point> convex_hull(const vector<Point> &points)
{
    int k = 0;
    vector<Point> result(2 * points.size());
    sort(points.begin(), points.end(), [](Point p, Point q) { return p.second > q.second || ((!(p.second < q.second) && p.first < q.first)); });
    for (int i = 0; i < points.size(); ++i) 
    {
        while (k >= 2 && cross(result[k - 2], result[k - 1], points[i]) <= 0)  k--;
        result[k++] = points[i];
    }
    for (int i = points.size() - 2, t = k + 1; i >= 0; i--) 
    {
        while (k >= t && cross(result[k - 2], result[k - 1], points[i]) <= 0) k--;
        result[k++] = points[i];
    }
    result.resize(k); //Circular - result[0] == result[k-1]
    return result; 
}
