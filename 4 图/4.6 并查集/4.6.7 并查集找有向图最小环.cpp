/*
 * 并查集找有向图的最小环
 * mins 变量中保存当前最小环，如果为 INT_MAX 则无最小环
 */
const int MAXN = 200010;

int f[MAXN];
int ranks[MAXN];
int mins;

int finds(int x)
{
    if (x == f[x])
        return x;
    else
    {
        int fn = finds(f[x]);
        ranks[x] += ranks[f[x]];
        return f[x] = fn;
    }
}
void unite(int x, int y)
{
    int px = finds(x);
    int py = finds(y);
    if (px != py)
    {
        f[px] = py;
        ranks[x] = ranks[y] + 1;
    }
    else
    {
        mins = min(mins, ranks[x] + ranks[y] + 1);
    }
}
void init(int b, int e)
{
    mins = INT_MAX;
    for (int i = b; i < e; i++)
    {
        ranks[i] = 0;
        f[i] = i;
    }
}