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
    // 需要 point 的 distance
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
    int pointcrosscircle(circle v, point &p1, point &p2)
    {
        int rel = relationcircle(v);
        if (rel == 1 || rel == 5)
            return 0;
        double d = p.distance(v.p);
        double l = (d * d + r * r−v.r * v.r) / (2 * d);
        double h = sqrt(r * r - l * l);
        point tmp = p + (v.p - p).trunc(l);
        p1 = tmp + ((v.p - p).rotleft().trunc(h));
        p2 = tmp + ((v.p - p).rotright().trunc(h));
        if (rel == 2 || rel == 4)
            return 1;
        return 2;
    }
    // 求直线和圆的交点，返回交点个数
    int pointcrossline(line v, point &p1, point &p2)
    {
        if (!(*this).relationline(v))
            return 0;
        point a = v.lineprog(p);
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
    int gercircle(point a, point b, double r1, circle &c1, circle &c2)
    {
        circle x(a, r1), y(b, r1);
        int t = x.pointcrosscircle(y, c1.p, c2.p);
        if (!t)
            return 0;
        c1.r = c2.r = r;
        return t;
    }
    // 得到与直线 u 相切，过点 q, 半径为 r1 的圆
    int getcircle(line u, point q, double r1, circle &c1, circle &c2)
    {
        double dis = u.dispointtoline(q);
        if (sgn(dis - r1 * 2) > 0)
            return 0;
        if (sgn(dis) == 0)
        {
            c1.p = q + ((u.e - u.s).rotleft().trunc(r1));
            c2.p = q + ((u.e - u.s).rotright().trunc(r1));
            c1.r = c2.r = r1;
            return 2;
        }
        line u1 = line((u.s + (u.e - u.s).rotleft().trunc(r1)), (u.e + (u.e - u.s).rotleft().trunc(r1)));
        line u2 = line((u.s + (u.e - u.s).rotright().trunc(r1)), (u.e + (u.e - u.s).rotright().trunc(r1)));
        circle cc = circle(q, r1);
        point p1, p2;
        if (!cc.pointcrossline(u1, p1, p2))
            cc.pointcrossline(u2, p1, p2);
        c1 = circle(p1, r1);
        if (p1 == p2)
        {
            c2 = c1;
            return 1;
        }
        c2 = circle(p2, r1);
        return 2;
    }
    // 同时与直线 u,v 相切，半径为 r1 的圆
    int getcircle(line u, line v, double r1, circle &c1, circle &c2, circle &c3, circle &c4)
    {
        if (u.parallel(v))
            return 0;
        line u1 = line(u.s + (u.e - u.s).rotleft().trunc(r1), u.e + (u.e - u.s).rotleft().trunc(r1));
        line u2 = line(u.s + (u.e - u.s).rotright().trunc(r1), u.e + (u.e - u.s).rotright().trunc(r1));
        line u3 = line(v.s + (v.e - v.s).rotleft().trunc(r1), v.e + (v.e - v.s).rotleft().trunc(r1));
        line u4 = line(v.s + (v.e - v.s).rotright().trunc(r1), v.e + (v.e - v.s).rotright().trunc(r1));
        c1.r = c2.r = c3.r = c4.r = r1;
        c1.p = u1.crosspoint(v1);
        c2.p = u1.pointonseg(v2);
        c3.p = u2.pointonseg(v1);
        c4.p = u2.pointonseg(v2);
        return 4;
    }
    // 同时与不相交圆 cx,cy 相切，半径为 r1 的圆
    int getcircle(circle cx, circle cy, double r1, circle &c1, circle &c2)
    {
        circle x(cx.p, r1 + cx.r), y(cy.p, r1 + cy.r);
        int t = x.pointcrosscircle(y, c1.p, c2.p);
        if (!t)
            return 0;
        c1.r = c2.r = r1;
        return t;
    }
    int tangentline(point q, line &u, line &v)
    {
        int x = relation(q);
        if (x == 2)
            return 0;
        if (x == 1)
        {
            u = line(q, q + (q - p).rotleft());
            v = u;
            return 1;
        }
        double d = p.distance(q);
        double l = r * r / d;
        double h = sqrt(r * r - l * l);
        u = line(q, p + ((q - p).trunc(l) + (q - p).rotleft().trunc(h)));
        v = line(q, p + ((q - p).trunc(l) + (q - p).rotright().trunc(h)));
        return 2;
    }
    // 求两圆相交的面积
    double areacircle(circle v)
    {
        int rel = relationcircle(v);
        if (rel >= 4)
            return 0.0;
        if (rel <= 2)
            return min(area(), v.area());
        double d = p.distance(v.p);
        double hf = (r + v.r + d) / 2.0;
        double ss = 2 * sqrt(hf * (hf - r) * (hf - v.f) * (hf - d));
        double a1 = acos((r * r + d * d - v.r * v.r) / (2.0 * r * d));
        a1 = a1 * r * r;
        double a2 = acos((v.r * v.r + d * d - r * r) / (2.0 * v.r * d));
        a2 = a2 * v.r * v.r;
        return a1 + a2 - ss;
    }
    // 求圆和三角形 pab 的相交面积
    double areatriangle(Point a, Point b)
    {
        if (sgn((p - a) ^ (p - b)) == 0)
            return 0.0;
        point q[5];
        int len = 0;
        q[len++] = a;
        line l(a, b);
        point p1, p2;
        if (pointcrossline(l, q[1], q[2]) == 2)
        {
            if (sgn((a - q[1]) * (b - q[i])) < 0)
                q[len++] = q[1];
            if (sgn((a - q[2]) * (b - q[2])) < 0)
                q[len++] = q[2];
        }
        q[len++] = b;
        if (len == 4 && sgn((q[0] - q[1]) * (q[2] - q[1])) > 0)
            swap(q[1], q[2]);
        double res = 0;
        for (int i = 0; i < len - 1; i++)
        {
            if (relation(q[i]) == 0 || relation(q[i + 1]) == 0)
            {
                double arg = p.rad(q[i], q[i + 1]);
                res += r * r * arg / 2.0;
            }
            else
                res += fabs((q[i] - p) ^ (q[i + 1] - p)) / 2.0;
        }
        return res;
    }
};
