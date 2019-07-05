// 此模板中使用到了point中的内容
#include "point.h"
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
struct line
{
    point s, e;
    line() {}
    line(point _s, point _e) : s(_s), e(_e) {}
    // 判断射线重合。如果要判断线段，可以使用先 adjust 一下
    bool operator==(line v)
    {
        return (s == v.s) && (e == v.e);
    }
    // 根据一个点和倾斜角 angle 确定直线,0 <= angle < pi
    line(point p, double angle)
    {
        s = p;
        if (sgn(angle - pi / 2) == 0)
        {
            e = (s + point(0, 1));
        }
        else
        {
            e = (s + point(1, tan(angle)));
        }
    }
    // 根据 ax + by + c = 0 确定直线
    line(double a, double b, double c)
    {
        if (sgn(a) == 0)
        {
            s = point(0, -c / b);
            e = point(1, -c / b);
        }
        else if (sgn(b) == 0)
        {
            s = point(-c / a, 0);
            e = point(-c / a, 1);
        }
        else
        {
            s = point(0, -c / b);
            e = point(1, (-c - a) / b);
        }
    }
    // 调整线段
    void adjust()
    {
        if (e < s)
            swap(s, e);
    }
    // 求线段长度
    double lenth()
    {
        return s.distance(e);
    }
    // 返回线段的倾斜角
    double angle()
    {
        double k = atan2(e.y - s.y, e.x - s.x);
        if (sgn(k) < 0)
            k += pi;
        if (sgn(k - pi) == 0)
            k -= pi;
        return k;
    }
    // 点和直线关系
    // 1 在左侧
    // 2 在右侧
    // 3 在直线上
    int relation(point p)
    {
        int c = sgn((p - s) ^ (e - s));
        if (c < 0)
            return 1;
        else if (c > 0)
            return 2;
        else
            return 3;
    }
    // 点在线段上的判断
    bool pointonseg(point p)
    {
        return sgn((p - s) ^ (e - s)) == 0 && sgn((p - s) * (p - e)) <= 0;
    }
    // 两向量平行 (对应直线平行或重合)
    bool parallel(line v)
    {
        return sgn((e - s) ^ (v.e - v.s)) == 0;
    }
    // 两线段相交判断
    // 2 规范相交
    // 1 非规范相交
    // 0 不相交
    int segcrossseg(line v)
    {
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        int d3 = sgn((v.e - v.s) ^ (s - v.s));
        int d4 = sgn((v.e - v.s) ^ (e - v.s));
        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
            reutrn 2;
        return (d1 == 0 && sgn((v.s - s) * (v.s - e)) <= 0) ||
               (d2 == 0 && sgn((v.e - s) * (v.e - e)) <= 0) ||
               (d3 == 0 && sgn((s - v.s) * (s - v.e)) <= 0) ||
               (d4 == 0 && sgn((e - v.s) * (e - v.e)) <= 0);
    }
    // 直线和线段相交判断
    // this -> line
    // v    -> seg
    // 2 规范相交
    // 1 非规范相交
    // 0 不相交
    int linecrossseg(line v)
    {
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        if ((d1 ^ d2) == -2)
            return 2;
        return (d1 == 0 || d2 == 0);
    }
    // 两直线关系
    // 0 平行
    // 1 重合
    // 2 相交
    int linecrossline(line v)
    {
        if ((*this).parallel(v))
            return v.relation(s) == 3;
        return 2;
    }
    // 求两直线的交点
    // 要保证两直线不平行或重合
    point crosspoint(line v)
    {
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
    }
    // 点到直线的距离
    double dispointtoline(point p)
    {
        return fabs((p - s) ^ (e - s)) / lenth();
    }
    // 点到线段的距离
    double dispointtoseg(point p)
    {
        if (sgn((p−s) * (e−s)) < 0 || sgn((p−e) * (s−e)) < 0)
            return min(p.distance(s), p.distance(e));
        return dispointtoline(p);
    }
    // 返回线段到线段的距离
    // 前提是两线段不相交，相交距离就是 0 了
    double dissegtoseg(line v)
    {
        return min(min(dispointtoseg(v.s), dispointtoseg(v.e)), min(v.dispointtoseg(s), v.dispointtoseg(e)));
    }
    // 返回点 p 在直线上的投影
    Point lineprog(Point p)
    {
        return s + (((e - s) * ((e - s) * (p - s))) / ((e - s).len2()));
    }
    // 返回点 p 关于直线的对称点
    Point symmetrypoint(Point p)
    {
        Point q = lineprog(p);
        return Point(2 * q.x - p.x, 2 * q.y - ]-p.y);
    }
};

// 简易版本的线段相交
struct line
{
    double x1;
    double y1;
    double x2;
    double y2;
};
bool intersection(const line &l1, const line &l2)
{
    //快速排斥实验
    if ((l1.x1 > l1.x2 ? l1.x1 : l1.x2) < (l2.x1 < l2.x2 ? l2.x1 : l2.x2) ||
        (l1.y1 > l1.y2 ? l1.y1 : l1.y2) < (l2.y1 < l2.y2 ? l2.y1 : l2.y2) ||
        (l2.x1 > l2.x2 ? l2.x1 : l2.x2) < (l1.x1 < l1.x2 ? l1.x1 : l1.x2) ||
        (l2.y1 > l2.y2 ? l2.y1 : l2.y2) < (l1.y1 < l1.y2 ? l1.y1 : l1.y2))
    {
        return false;
    }
    //跨立实验
    if ((((l1.x1 - l2.x1) * (l2.y2 - l2.y1) - (l1.y1 - l2.y1) * (l2.x2 - l2.x1)) *
         ((l1.x2 - l2.x1) * (l2.y2 - l2.y1) - (l1.y2 - l2.y1) * (l2.x2 - l2.x1))) > 0 ||
        (((l2.x1 - l1.x1) * (l1.y2 - l1.y1) - (l2.y1 - l1.y1) * (l1.x2 - l1.x1)) *
         ((l2.x2 - l1.x1) * (l1.y2 - l1.y1) - (l2.y2 - l1.y1) * (l1.x2 - l1.x1))) > 0)
    {
        return false;
    }
    return true;
}