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
    // 面积
    double area()
    {
        return pi * r * r;
    }
    // 周长
    double circumference()
    {
        return 2 * pi * r;
    }
    // 点圆关系
    // 0 圆外
    // 1 圆上
    // 2 圆内
    int relation(point b)
    {
        double dst = b.distance(p);
        if (sgn(dst - r) < 0)
            return 2;
        else if (sgn(dst - r) == 0)
            return 1;
        return 0;
    }
    // 线段和圆的关系
    // // 需要 line 的 dispointtoseg
    int relationseg(line v)
    {
        double dst = v.dispointtoseg(p);
        if (sgn(dst - r) < 0)
            return 2;
        else if (sgn(dst - r) == 0)
            return 1;
        return 0;
    }
    // 直线和圆的关系
    // // 需要 line 的 dispointtoline
    int relationline(line v)
    {
        double dst = v.dispointtoline(p);
        if (sgn(dst - r) < 0)
            return 2;
        else if (sgn(dst - r) == 0)
            return 1;
        return 0;
    }
    // 两圆的关系
    // 5 相离
    // 4 外切
    // 3 相交
    // 2 内切
    // 1 内含
    // 需要 Point 的 distance
    int relationcircle(circle v)
    {
        double d = p.distance(v.p);
        if (sgn(d - r - v.r) > 0)
            return 5;
        if (sgn(d - r - v.r) == 0)
            return 4;
        double l = fabs(r - v.r);
        if (sgn(d - r - v.r) < 0 && sgn(d - l) > 0)
            return 3;
        if (sgn(d - l) == 0)
            return 2;
        if (sgn(d - l) < 0)
            return 1;
    }
    // 求两个圆的交点，返回 0 表示没有交点，返回 1 是一个交点，2 是两个交点
    // 需要 relationcircle
    int pointcrosscircle(circle v, Point &p1, Point &p2)
    {
        int rel = relationcircle(v);
        if (rel == 1 || rel == 5)
            return 0;
        double d = p.distance(v.p);
        double l = (d * d + r * r−v.r * v.r) / (2 * d);
        double h = sqrt(r * r - l * l);
        Point tmp = p + (v.p - p).trunc(l);
        p1 = tmp + ((v.p - p).rotleft().trunc(h));
        p2 = tmp + ((v.p - p).rotright().trunc(h));
        if (rel == 2 || rel == 4)
            return 1;
        return 2;
    }
    // 求直线和圆的交点，返回交点个数
    int pointcrossline(Line v, Point &p1, Point &p2)
    {
        if (!(*this).relationline(v))
            return 0;
        Point a = v.lineprog(p);
        double d = v.dispointtoline(p);
        d = sqrt(r * r - d * d);
        if (sgn(d) == 0)
        {
            p1 = a;
            p2 = a;
            return 1;
        }
        p1 = a + (v.e - v.s).trunc(d);
        p2 = a - (v.e - v.s).trunc(d);
        return 2;
    }
    // 得到过 a,b 两点，半径为 r1 的两个圆
    // 需要 pointcrosscircle
    int gercircle(Point a, Point b, double r1, circle &c1, circle &c2)
    {
        circle x(a, r1), y(b, r1);
        int t = x.pointcrosscircle(y, c1.p, c2.p);
        if (!t)
            return 0;
        c1.r = c2.r = r;
        return t;
    }
};
