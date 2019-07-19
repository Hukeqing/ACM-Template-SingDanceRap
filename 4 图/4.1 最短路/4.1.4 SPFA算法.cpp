/*
 * SPFA 算法
 * 支持负权边，检测负权回路
 * 先 init 一下
 * 然后将边信息写入 matrix 矩阵
 */
#define MAXN 1010

int matrix[MAXN][MAXN]; //邻接矩阵
bool visited[MAXN];     //标记数组
int dist[MAXN];         //源点到顶点i的最短距离
int path[MAXN];         //记录最短路的路径
int enqueue_num[MAXN];  //记录入队次数
int vertex_num;         //顶点数
int edge_num;           //边数
int source;             //源点

bool SPFA()
{
    memset(visited, 0, sizeof(visited));
    memset(enqueue_num, 0, sizeof(enqueue_num));
    for (int i = 0; i < vertex_num; i++)
    {
        dist[i] = INT_MAX;
        path[i] = source;
    }

    queue<int> Q;
    Q.push(source);
    dist[source] = 0;
    visited[source] = true;
    enqueue_num[source]++;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        visited[u] = 0;
        for (int v = 0; v < vertex_num; v++)
        {
            if (matrix[u][v] != INT_MAX) //u与v直接邻接
            {
                if (dist[u] + matrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + matrix[u][v];
                    path[v] = u;
                    if (!visited[v])
                    {
                        Q.push(v);
                        enqueue_num[v]++;
                        if (enqueue_num[v] >= vertex_num)
                            return false;
                        visited[v] = 1;
                    }
                }
            }
        }
    }
    return true;
}
void getroad(int n, int *road)
{
    int p = n;
    stack<int> s;
    while (source != p)
    {
        s.push(p);
        p = path[p];
    }
    road[0] = source;
    int cur = 1;
    while (!s.empty())
    {
        road[cur++] = s.top();
        s.pop();
    }
}
void init()
{
    for (int i = 0; i < vertex_num; i++)
        for (int j = 0; j < vertex_num; j++)
            matrix[i][j] = INT_MAX; //初始化matrix数组
}