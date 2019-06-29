/*
 * 单源最短路径，Dijkstra 算法，邻接矩阵形式，复杂度为O(n^2)
 * 求出源 beg 到所有点的最短路径，传入图的顶点数，和邻接矩阵 cost[][]
 * 返回各点的最短路径 lowcost[], 路径 pre[].pre[i] 记录 beg 到 i 路径上的父结点，pre[beg]=-1
 * 可更改路径权值类型，但是必须非负
 */

#define typec int
const int MAXN = 1010;
const typec INF = 0x3f3f3f3f; //防止后面溢出，这个不能太大
bool vis[MAXN];
int pre[MAXN];
void Dijkstra(typec cost[][MAXN], typec lowcost[], int n, int beg)
{
    for (int i = 0; i < n; i++)
    {
        lowcost[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    lowcost[beg] = 0;
    for (int j = 0; j < n; j++)
    {
        int k = -1;
        int Min = INF;
        for (int i = 0; i < n; i++)
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
        for (int i = 0; i < n; i++)
        {
            if (!vis[i] && lowcost[k] + cost[k][i] < lowcost[i])
            {
                lowcost[i] = lowcost[k] + cost[k][i];
                pre[i] = k;
            }
        }
    }
}
