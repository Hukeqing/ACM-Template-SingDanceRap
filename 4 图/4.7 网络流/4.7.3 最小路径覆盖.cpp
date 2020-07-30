/*
 * 借助 ISAP 的最小路径覆盖问题
 * 点编号为 1 - n
 * 首先使用 init 函数进行初始化
 * 用 addedge 加边
 * 用 maxflow 函数返回路径数
 */
#define MAXN 160  // 点数
#define MAXM 6010 // 边数
int n, m;
struct edge {
    int y, next, c;
};
edge s[MAXM * 2];
int first[MAXN * 2];
int len = 1;
int begin, end; // 网络流的起始点和结束点
int h[MAXN * 2];
int p[MAXN * 2];
int match[MAXN * 2]; // 如果不需要输出边的内容，则不需要这个变量
bool tf[MAXN * 2];   // 如果不需要输出边的内容，则不需要这个变量
// 加边，单项边三个参数，双向边四个参数
void addedge(int x, int y, int w, int rw = 0) {
    y += n;
    len++;
    s[len].y = y;
    s[len].c = w;
    s[len].next = first[x];
    first[x] = len;
    len++;
    s[len].y = x;
    s[len].c = rw;
    s[len].next = first[y];
    first[y] = len;
}
bool bfs() {
    memset(h, 0, sizeof(h));
    queue<int> f;
    h[begin] = 1;
    f.push(begin);
    while (!f.empty()) {
        int x = f.front();
        for (int i = first[x]; i != 0; i = s[i].next) {
            int y = s[i].y;
            if (h[y] == 0 && s[i].c > 0) {
                h[y] = h[x] + 1;
                f.push(y);
            }
        }
        f.pop();
    }
    return h[end];
}
int dfs(int x, int t) {
    if (x == end)
        return t;
    int tot = 0;
    for (int i = first[x]; i != 0; i = s[i].next) {
        int y = s[i].y;
        if (tot == t)
            return t;
        if (h[y] == h[x] + 1 && s[i].c > 0) {
            int now = dfs(y, min(s[i].c, t - tot));
            tot += now;
            s[i].c -= now;
            s[i ^ 1].c += now;
            if (now != 0 && x != begin && y != end) {
                match[x] = y - n;
                p[y - n] = x;
            }
        }
    }
    if (tot == 0)
        h[x] = 0;
    return tot;
}
void maxflowaddedge(int x, int y, int w) {
    len++;
    s[len].y = y;
    s[len].c = w;
    s[len].next = first[x];
    first[x] = len;
    len++;
    s[len].y = x;
    s[len].c = 0;
    s[len].next = first[y];
    first[y] = len;
}
void init() {
    for (int i = 1; i <= n; i++)
        match[i] = p[i] = i;
}
// 调用此函数求解，返回最小路径数
int maxflow() {
    for (int i = 1; i <= n; i++) {
        maxflowaddedge(begin, i, 1);
        maxflowaddedge(i + n, end, 1);
    }
    int flow = 0;
    while (bfs()) {
        int dx = dfs(begin, 1e9);
        while (dx != 0) {
            flow += dx;
            dx = dfs(begin, 1e9);
        }
    }
    return n - flow;
}
// 下面两个为边的输出函数，视情况添加
void out_put(int x) {
    if (x == 0)
        return;
    if (p[x] != x)
        out_put(p[x]);
    tf[x] = true;
    cout << x << " ";
}
void print() {
    memset(tf, false, sizeof(tf));
    for (int i = 1; i <= n; i++) {
        if (match[i] == i && tf[i] == false) {
            out_put(i);
            cout << "\n";
        }
    }
}