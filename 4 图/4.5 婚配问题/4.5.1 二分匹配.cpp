/*
 * 二分匹配
 * 每组数据使用前使用 init 函数初始化
 * 将数据输入到变量 line、m、n 中
 * 调用 solve 函数求解
 */
const int MAXN = 110; // 人数

bool line[MAXN][MAXN], isget[MAXN]; // line[i][j] 为女生 i 对男生 j 是否有好感
int boys[MAXN];
int m, n; // m 为男生个数，n 为女生个数

bool finds(int x)
{
    for (int i = 1; i <= m; i++)
    {
        if (line[x][i] && !isget[i])
        {
            isget[i] = true;
            if (boys[i] == 0 || finds(boys[i]))
            {
                boys[i] = x;
                return true;
            }
        }
    }
    return false;
}
void init()
{
    memset(line, 0, sizeof(line));
}
int solve()
{
    memset(boys, 0, sizeof(boys));
    int ans = 0;
    for (size_t i = 1; i <= n; i++)
    {
        memset(isget, 0, sizeof(isget));
        if (finds(i))
            ans++;
    }
    return ans;
}