/*
 * 并查集
 * 1、并查集数量：finds(i) == i 的数量
 * 2、判无向图环：unite 时，x == y 则有环
 * 3、
 */
const int MAXN = 1010;

int f[MAXN];

int finds(int x) {
    return x == f[x] ? x : f[x] = finds(f[x]);
}
void unite(int x, int y) {
    rx = finds(x);
    ry = finds(y);
    if (rx != ry)
        f[rx] = ry;
}
void init(int b, int e) { // 初始化函数，范围为 [b, e)
    for (int i = b; i < e; i++)
        f[i] = i;
}
