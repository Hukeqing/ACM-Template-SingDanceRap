/*
 * 本头文件的所有函数可以在当前目录下的"点与向量运算.cpp"中找到
 */

struct point
{
    double x, y;
    point();
    point(double _x, double _y);
    bool operator<(Point b) const;          // 点左右判断 - line 中使用
    bool operator==(point b) const;         // 点相等判断
    point operator+(const point &b) const;  // 向量相加
    point operator-(const point &b) const;  // 向量相减
    point operator*(const double &k) const; // 向量乘法
    point operator/(const double &k) const; // 向量除法
    point trunc(double r) const;            // 向量模转换
    double operator*(const point &b) const; // 向量点积
    double operator^(const Point &b) const; // 向量叉积
    double len(bool isSqrt = true);         // 向量模长度，参数为是否开平方
    double distance(const point &other);    // 点距离
    point rotleft();                        // 向量绕原点逆时针旋转 90 度
    point rotright();                       // 向量绕原点顺时针旋转 90 度
    point rotate(point p, double angle);    // 绕 p 点逆时针旋转 angle 度
    double rad(point a, point b);           // 计算点 this、a、b 组成的角的角度，角的两条射线为 this-a、this-b
};