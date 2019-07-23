/*
 * SPFA 算法邻接表
 * 支持负权边，检测负权回路
 * 先 init 一下
 * 用 addedge 函数加边
 */
#define MAXN 1010      // 点数
#define MAXM 10010     // 边数
bool visited[MAXN];    //标记数组
int dist[MAXN];        //源点到顶点i的最短距离
int path[MAXN];        //记录最短路的路径
int enqueue_num[MAXN]; //记录入队次数

struct Edge
{
    int to, next, cost;
} edge[MAXM];
int tot;
int head[MAXN];
void init(int n) // 参数为点编号的最大值
{
    tot = 0;
    memset(head, -1, sizeof(int) * n);
}
void addedge(int u, int v, int w)
{
    edge[tot].to = v;
    edge[tot].cost = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}
bool SPFA(int b, int e, int start)
{
    memset(visited, false, sizeof(visited));
    memset(enqueue_num, 0, sizeof(enqueue_num));
    for (int i = b; i < e; i++)
    {
        dist[i] = INT_MAX;
        path[i] = start;
    }
    queue<int> Q;
    Q.push(start);
    dist[start] = 0;
    visited[start] = true;
    enqueue_num[start]++;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        visited[u] = 0;
        for (int v = head[u]; v != -1; v = edge[v].next)
        {
            if (dist[u] + edge[v].cost < dist[v])
            {
                dist[v] = dist[u] + edge[v].cost;
                path[v] = u;
                if (!visited[v])
                {
                    Q.push(v);
                    enqueue_num[v]++;
                    if (enqueue_num[v] >= e)
                        return false;
                    visited[v] = 1;
                }
            }
        }
    }
    return true;
}
void getroad(int start, int end, int *road)
{
    int p = end;
    stack<int> s;
    while (start != p)
    {
        s.push(p);
        p = path[p];
    }
    road[0] = start;
    int cur = 1;
    while (!s.empty())
    {
        road[cur++] = s.top();
        s.pop();
    }
}