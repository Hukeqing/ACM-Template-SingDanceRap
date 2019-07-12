/*
 * Prim求MST
 * 耗费矩阵 cost[][]，标号从 0 开始，0∼n-1
 * 返回最小生成树的权值，返回 -1 表示原图不连通
 */

const int MAXN = 110;
bool vis[MAXN];
int lowc[MAXN];
int Prim(int cost[MAXN][MAXN], int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    vis[0] = true;
    for (int i = 1; i < n; i++)
        lowc[i] = cost[0][i];
    for (int i = 1; i < n; i++)
    {
        int minc = INT_MAX;
        int p = -1;
        for (int j = 0; j < n; j++)
            if (!vis[j] && minc > lowc[j])
            {
                minc = lowc[j];
                p = j;
            }
        if (minc == INT_MAX)
            return -1;
        ans += minc;
        vis[p] = true;
        for (int j = 0; j < n; j++)
            if (!vis[j] && lowc[j] > cost[p][j])
                lowc[j] = cost[p][j];
    }
    return ans;
}
