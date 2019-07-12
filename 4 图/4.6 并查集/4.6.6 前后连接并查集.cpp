/*
 * 前后连接的并查集
 * 使用 unite 函数时会把 x 中的元素连接到 y 后面
 * 可以求任意两点间距离，如果不在一个并查集中就返回 -1
 * num 保存了对应并查集中的元素个数， rank 保存了对应的元素至当前队头的距离
 */

const int MAXN = 30010;

int f[MAXN];
int ranks[MAXN];
int num[MAXN];

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
    x = finds(x);
    y = finds(y);
    if (x != y)
    {
        ranks[x] += num[y];
        f[x] = y;
        num[y] += num[x];
        num[x] = 0;
    }
}
void init(int b, int e)
{
    for (int i = b; i < e; i++)
    {
        ranks[i] = 0;
        num[i] = 1;
        f[i] = i;
    }
}
int dist(int x, int y)
{
    int x = finds(a);
    int y = finds(b);
    if (x != y)
        return -1;
    else
        return abs(ranks[x] - ranks[y]);
}