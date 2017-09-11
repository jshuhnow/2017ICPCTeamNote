struct Point {
    int x, y;
};
struct Line {
    Point p1, p2;
};

int get_dist(Line l, Line r) {
    if (l.p1.x > l.p2.x) swap(l.p1, l.p2);
    if (l.p1.y > l.p2.y) swap(l.p1, l.p2);
    if (r.p1.x > r.p2.x) swap(r.p1, r.p2);
    if (r.p1.y > r.p2.y) swap(r.p1, r.p2);
    if (r.p1.x == r.p2.x) swap(l, r);
    const int INF = 2e9;
    int res = INF;
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
