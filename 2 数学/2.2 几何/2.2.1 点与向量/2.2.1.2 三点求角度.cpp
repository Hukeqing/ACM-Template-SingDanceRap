struct point
{
    double x, y;
    point() {}
    point(double _x, double _y) : x(_x), y(_y) { }
    point operator *(const double &b)const{
        return point(x * k, y * k);
    }
    
};

double rad(point a, point b, point mid)
{
    return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
}