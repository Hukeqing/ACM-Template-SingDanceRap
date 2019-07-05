const double eps = 1e-8;

int sgn(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    return 1;
}
struct point
{
    double x, y;
    point() {}
    point(double _x, double _y) : x(_x), y(_y) {}
    // 点左右判断 - line 中使用
    bool operator<(Point b) const
    {
        return sgn(x−b.x) == 0 ? sgn(y−b.y) < 0 : x < b.x;
    }
    // 点相等判断
    bool operator==(point b) const
    {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    // 向量相加
    point operator+(const Point &b) const
    {
        return Point(x + b.x, y + b.y);
    }
    // 向量相减
    point operator-(const point &b) const
    {
        return point(x - b.x, y - b.y);
    }
    // 向量乘法
    point operator*(const double &k) const
    {
        return point(x * k, y * k);
    }
    // 向量除法
    point operator/(const double &k) const
    {
        return point(x / k, x / k);
    }
    // 向量模转换
    point trunc(double r) const
    {
        double l = len();
        if (!sgn(l))
            return *this;
        r /= l;
        return point(x * r, y * r);
    }
    // 向量点积
    double operator*(const point &b) const
    {
        return x * b.x + y * b.y;
    }
    // 向量叉积
    double operator^(const Point &b) const
    {
        return x * b.y - y * b.x;
    }
    // 向量模长度，参数为是否开平方
    double len(bool isSqrt = true)
    {
        return isSqrt ? hypot(x, y) : (x * x + y * y);
    }
    // 点距离
    double distance(const point &other)
    {
        return hypot(x - other.x, y - other.y);
    }
    // 向量绕原点逆时针旋转 90 度
    point rotleft()
    {
        return point(-y, x);
    }
    // 向量绕原点顺时针旋转 90 度
    point rotright()
    {
        return point(y, -x);
    }
    // 绕 p 点逆时针旋转 angle 度
    point rotate(point p, double angle)
    {
        point v = (*this) - p;
        double c = cos(angle), s = sin(angle);
        return point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
};
// 计算点 mid、a、b 组成的角的角度，角的两条射线为 mid-a、mid-b
double rad(point a, point b, point mid)
{
    return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
}