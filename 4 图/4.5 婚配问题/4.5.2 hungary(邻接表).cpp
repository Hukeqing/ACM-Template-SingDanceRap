/*
 * 二分匹配(邻接表)——匈牙利算法
 * 每组数据使用前使用 init 函数初始化，给 uN 赋值
 * 加边使用函数 addedge(u, v)
 * 点的编号 0~uN - 1点的编号 0~uN - 1
 */

const int MAXN = 5010;  //点数的最大值
const int MAXM = 50010; //边数的最大值
struct Edge {
    int to, next;
} edge[MAXM];
int head[MAXN], tot;
inline void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int linker[MAXN];
bool used[MAXN];
int uN; // 点的个数
bool dfs(int u) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!used[v]) {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v])) {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    int res = 0;
    memset(linker, -1, sizeof(linker));
    // 点的编号 0~uN - 1
    for (int u = 0; u < uN; u++) {
        memset(used, false, sizeof(used));
        if (dfs(u))
            res++;
    }
    return res;
}
