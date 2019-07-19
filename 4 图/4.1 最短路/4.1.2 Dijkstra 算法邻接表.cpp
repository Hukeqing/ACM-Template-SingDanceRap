/*
 * 单源最短路径，Dijkstra 算法，邻接表形式，复杂度为O(n^2)
 * 求出源 start 到所有点的最短路径
 * 返回各点的最短路径 lowcost[], 路径 pre[].pre[i] 记录 start 到 i 路径上的父结点，pre[start]=-1
 * 路径权值必须非负
 * 点编号为 [b, e)
 */

const int MAXN = 2600;  // 点数
const int MAXM = 12600; // 边数

struct Edge
{
    int to, next, cost;
} edge[MAXM];
int tot;
int head[MAXN];
int lowcost[MAXN];
bool vis[MAXN];
int pre[MAXN];
void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w, int rw = -1)
{
    edge[tot].to = v;
    edge[tot].cost = w;
    edge[tot].next = head[u];
    head[u] = tot++;
    if (rw < 0)
        return;
    edge[tot].to = u;
    edge[tot].cost = rw;
    edge[tot].next = head[v];
    head[v] = tot++;
}
void Dijkstra(int b, int e, int start)
{
    for (int i = b; i < e; i++)
    {
        lowcost[i] = INT_MAX;
        vis[i] = false;
        pre[i] = -1;
    }
    lowcost[start] = 0;
    vis[start] = true;
    int curedge = head[start];
    while (curedge != -1)
    {
        if (!vis[edge[curedge].to] && lowcost[start] + edge[curedge].cost < lowcost[edge[curedge].to])
        {
            lowcost[edge[curedge].to] = lowcost[start] + edge[curedge].cost;
            pre[edge[curedge].to] = start;
        }
        curedge = edge[curedge].next;
    }
    for (int j = b; j < e - 1; j++)
    {
        int k = -1;
        int Min = INT_MAX;
        for (int i = b; i < e; i++)
        {
            if (!vis[i] && lowcost[i] < Min)
            {
                Min = lowcost[i];
                k = i;
            }
        }
        if (k == -1)
            break;
        vis[k] = true;
        int curedge = head[k];
        while (curedge != -1)
        {
            if (!vis[edge[curedge].to] && lowcost[k] + edge[curedge].cost < lowcost[edge[curedge].to])
            {
                lowcost[edge[curedge].to] = lowcost[k] + edge[curedge].cost;
                pre[edge[curedge].to] = k;
            }
            curedge = edge[curedge].next;
        }
    }
}