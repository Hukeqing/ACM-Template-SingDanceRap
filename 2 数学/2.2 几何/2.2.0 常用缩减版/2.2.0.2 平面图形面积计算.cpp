const int MAXN = 1000;

struct point
{
    double x, y;
};

point nlist[MAXN];

inline double solve(int n)
{
    double area = 0, step = nlist[0].x * nlist[n - 1].y - nlist[n - 1].x * nlist[0].y;
    for (int i = 1; i < n; i++)
        area += nlist[i - 1].x * nlist[i].y - nlist[i].x * nlist[i - 1].y;
    return (fabs(area) - step) / 2;
}
