/*
 * 最大团问题，求哪些点组成最大团
 * 支持多组数据
 * 读入邻接矩阵保存在 mp 数组中
 * 变量 n 保存的是点的个数
 * 调用 solve 函数求解
 * cnt 中为最大团的点数
 * ans 中从保存了最大团的点，编号 1 - cnt
 */
#define N 105 // 最大点数

int n, m;
bool mp[N][N];
int get[N][N];
int node[N], ans[N], dp[N];
int cnt;

void dfs(int now, int sum)
{
    if (sum == 0)
    {
        if (now > cnt)
        {
            cnt = now;
            for (int i = 1; i <= cnt; i++)
                ans[i] = node[i];
        }
        return;
    }
    for (int i = 1; i <= sum; i++)
    {
        int v = get[now][i], t = 0;
        if (now + dp[v] <= cnt)
            return;
        for (int j = i + 1; j <= sum; j++)
        {
            if (mp[v][get[now][j]])
                get[now + 1][++t] = get[now][j];
        }
        node[now + 1] = v;
        dfs(now + 1, t);
    }
}
void solve()
{
    cnt = 0;
    for (int i = n; i >= 1; i--)
    {
        int sum = 0;
        for (int j = i + 1; j <= n; j++)
        {
            if (mp[i][j])
                get[1][++sum] = j;
        }
        node[1] = i;
        dfs(1, sum);
        dp[i] = cnt;
    }
}