// 此模板中使用到了 point 中的内容
#include "point.h"
// 此模板中使用到了 line 中的内容
#include "line.h"

const double eps = 1e-8;
const double pi = acos(−1.0);

int sgn(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    return 1;
}

struct circle
{
    point p;  // 圆心
    double r; // 半径
    circle() {}
    circle(point _p, double _r) : p(_p), r(_r) {}
    // 三点求算外接圆、内切圆
    // 需要 point 的 + / rotate() 以及 line 的 crosspoint()
    // bool 变量表示是否为外接圆
    circle(point a, point b, point c, bool isCircumcircle)
    {
        if (isCircumcircle)
        {
            line u = line((a + b) / 2, ((a + b) / 2) + ((b - a).rotleft()));
            line v = line((b + c) / 2, ((a + c) / 2) + ((c - b).rotleft()));
            p = u.crosspoint(v);
            r = p.distance(a);
        }
        else
        {
            line u, v;
            double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y.c.x - a.x);
            u.s = a;
            u.e = u.s + point(cos((n + m) / 2), sin((n + m) / 2));
            v.s = b;
            m = atan2(a.y - b.y, a.x - b.x);
            n = atan2(c.y - b.y, c.x - b.x);
            p = u.crosspoint(v);
            r = line(a, b).dispointtoseg(p);
        }
    }
    bool operator==(circle v)
    {
        return (p == v.p) && sgn(r - v.r) == 0;
    }
    bool operator<(circle v) const
    {
        return ((p < v.p) || ((p == v.p) && sgn(r - v.r) < 0));
    }
};
