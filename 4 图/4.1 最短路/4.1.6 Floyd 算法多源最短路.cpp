/*
 * Floyd 算法
 * 复杂度O(N^3)
 * 多源时高效、可负权、稠密图效果好
 */
#define MAXN "edit"
int g[MAXN][MAXN]; // 算法中的 G 矩阵

// 插入一条带权有向边
void insert(int u, int v, int w)
{
    g[u][v] = w;
}

// 核心代码
void floyd()
{
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (g[i][k] + g[k][j] < g[i][j])
                    g[i][j] = g[i][k] + g[k][j];
}
// 初始化 g 矩阵
void init()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i == j)
                g[i][j] = 0;
            else
                g[i][j] = INT_MAX;
}