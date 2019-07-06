const int MAXN = 1010;

int f[MAXN];

int finds(int x)
{
    return x == f[x] ? x : f[x] = finds(f[x]);
}
void unite(int x, int y)
{
    x = finds(x);
    y = finds(y);
    if (x != y)
        f[x] = y;
}
void init(int b, int e) // 初始化函数，范围为 [b, e)
{
    for (int i = b; i < e; i++)
        f[i] = i;
}
int count(int b, int e) // 并查集个数
{
    int ans = 0;
    for (int i = b; i < e; i++)
        if (finds(i) == i)
            ans++;
    return ans;
}