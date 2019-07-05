/*
 * 本头文件的所有函数可以在当前目录下的"线段直线运算.cpp"中找到
 */
struct line
{
    point s, e;
    line();
    line(point _s, point _e);
    bool operator==(line v);            // 判断射线重合
    line(point p, double angle);        // 根据一个点和倾斜角 angle 确定直线,0 <= angle < pi
    line(double a, double b, double c); // 根据 ax + by + c = 0 确定直线
    void adjust();                      // 调整线段
    double lenth();                     // 求线段长度
    double angle();                     // 返回线段的倾斜角
    int relation(point p);              // 点和直线关系
    bool pointonseg(point p);           // 点在线段上的判断
    bool parallel(line v);              // 两向量平行 (对应直线平行或重合)
    int segcrossseg(line v);            // 两线段相交判断
    int linecrossseg(line v);           // 直线和线段相交判断
    int linecrossline(line v);          // 两直线关系
    point crosspoint(line v);           // 求两直线的交点
    double dispointtoline(point p);     // 点到直线的距离
    double dispointtoseg(point p);      // 点到线段的距离
    double dissegtoseg(line v);         // 返回线段到线段的距离
    Point lineprog(Point p);            // 返回点 p 在直线上的投影
    Point symmetrypoint(Point p);       // 返回点 p 关于直线的对称点
}