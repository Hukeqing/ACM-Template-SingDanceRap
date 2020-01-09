/*
 * 无向图找环
 * 如果有环，调用 unite 时会返回 true
 */
const int MAXN = 1010;

int f[MAXN];

int finds(int x)
{
    return x == f[x] ? x : f[x] = finds(f[x]);
}
bool unite(int x, int y)
{
    int px = finds(x);
    int py = finds(y);
    if (px != py)
    {
        f[px] = py;
        return false;
    }
    else
        return true;
}
void init(int b, int e)
{
    for (int i = b; i < e; i++)
        f[i] = i;
}