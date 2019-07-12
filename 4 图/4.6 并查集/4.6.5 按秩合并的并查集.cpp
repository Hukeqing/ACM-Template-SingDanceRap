const int MAXN = 1010;

int f[MAXN];
int ranks[MAXN];

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
        if (ranks[x] <= ranks[y])
        {
            fa[x] = y;
            ranks[y] = max(ranks[y], ranks[x] + 1)
        }
        else
        {
            fa[y] = x;
            ranks[x] = max(ranks[x], ranks[y] + 1);
        }
    }
}
void init(int b, int e)
{
    for (int i = b; i < e; i++)
    {
        ranks[i] = 1;
        f[i] = i;
    }
}