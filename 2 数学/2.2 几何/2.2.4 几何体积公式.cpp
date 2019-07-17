#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1.0);

//圆锥体体积公式 V = 1 / 3 * S * h, S是底面积, h是高
double volumn_Cone(double r, double h){
	return 1.0 / 3 * r * r * pi * h;
}

//三棱锥体积公式
//已知空间内三角形三顶点坐标A(a1, a2, a3), B(b1, b2, b3), C(c1, c2, c3).
//O为原点，则三棱锥O-ABC体积为
//V = 1.0 / 6 * abs(a1 * b2 * c3 + b1 * c2 * a3 + c1 * a2 * b3 - a1 * c2 * b3 - b1 * a2 * c3 - c1 * b2 * a3);
struct Point{
	double x;
	double y;
	double z;
};

double volumn_a(Point a, Point b, Point c){
	return 1.0 / 6 * abs(a.x * b.y * c.z + b.x * c.y * a.z + c.x * z.y * b.z - a.x * c.y * b.z - b.x * a.y * c.z - c.x * b.y * a.z);
}

//椭球在xyz-笛卡尔坐标系中的标准方程是:(x - x0) ^ 2 / a ^ 2 + (y - y0) ^ 2 / b ^ 2 + (z - z0) ^ 2 / c ^ 2 = 1
//体积是V = 4 / 3 * pi * a * b * c;
double volumn_Ellipse(double a, double b, double c){
	return 4.0 / 3 * pi * a * b * c;
}

//圆台的体积
double volumn_RoundTable(double R, double r, double h){
	return pi * h / 3.0 * (R * R + r * r + R * r);
}

//球缺
double volumn_MissingBall(double h, double r){
	return pi * h * h * (r - h / 3.0);
}

//交叉圆柱体的体积
double volumn_CrossCylinder(double h1, double h2, double r){
	return pi * r * r * (h1 + h2 - 2.0 / 3 * r);
}

//梯形体的体积
double volumn_TrapezoidalBody(double a, double b, double h1, double a1, double b1){
	return h / 6 * ((2 * a + a1) * b + (2 * a1 + a) * b1);
	//或者return h / 6 * (a * b + (a + a1) * (b + b1) + a1 * b1);
}