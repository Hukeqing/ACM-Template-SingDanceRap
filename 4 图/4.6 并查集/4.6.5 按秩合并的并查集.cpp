const int MAXN = 1010;

int f[MAXN];
int rank[MAXN];

int finds(int x)
{
    return x == f[x] ? x : f[x] = finds(f[x]);
}
void unite(int x, int y)
{
    x = finds(x);
    y = finds(y);
    if (x != y)
    {
        if (rank[x] <= rank[y])
        {
            fa[x] = y;
            rank[y] = max(rank[y], rank[x] + 1)
        }
        else
        {
            fa[y] = x;
            rank[x] = max(rank[x], rank[y] + 1);
        }
    }
}
void init(int b, int e)
{
    for (int i = b; i < e; i++)
    {
        rank[i] = 1;
        f[i] = i;
    }
}