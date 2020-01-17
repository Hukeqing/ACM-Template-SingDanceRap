/*
 * 可撤销并查集不可以路径压缩
 */
const int MAXN = "Edit";

int f[MAXN];
stack<pair<int, int>> s;

int finds(int x) {
    while (x ^ f[x])
        x = f[x];
    return x;
}
void unite(int x, int y) {
    x = finds(x);
    y = finds(y);
    if (x != y) {
        s.push({x, f[x]});
        f[x] = y;
    }
}
void init(int b, int e) { // 初始化函数，范围为 [b, e)
    for (int i = b; i < e; i++)
        f[i] = i;
}
void undo() {
    f[s.top().first] = s.top().second;
    s.pop();
}