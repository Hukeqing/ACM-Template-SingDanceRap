/*
 * Kruskal 算法求最小生成树
 * 每次使用前，把变量 tol 设置为 0
 * 使用 addedge 函数来插入边
 * 然后调用 Kruskal 函数求出答案
 */

const int MAXN = 110;   // 最大点数
const int MAXM = 10000; // 最大边数
int F[MAXN];            // 并查集使用
int tol;                // 边数，加边前赋值为 0
struct Edge {
    int u, v, w;
} edge[MAXN]; // 存储边的信息，包括起点/终点/权值

void addedge(int u, int v, int w) {
    edge[tol].u = u;
    edge[tol].v = v;
    edge[tol++].w = w;
}
// 排序比较函数
bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}
int find(int x) {
    if (F[x] == -1)
        return x;
    else
        return F[x] = find(F[x]);
}
// 传入点数，返回最小生成树的权值。
int Kruskal(int n) {
    memset(F, -1, sizeof(F));
    sort(edge, edge + tol, cmp);
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < tol; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;
        int t1 = find(u);
        int t2 = find(v);
        if (t1 != t2) {
            ans += w;
            F[t1] = t2;
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    if (cnt < n - 1)
        return -1;
    else
        return ans;
}