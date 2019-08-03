/* 
 * 一维RMQ ST算法 算法复杂度 O(nlog(n))
 * 数组下标 0 ~ n - 1
 * 构造RMQ数组 makermq(n, b) 或 makeRmqIndex(n, b)
 * dp[i][j] 表示从 i 到 i + 2 ^ j - 1中最小的一个值(从 i 开始持续 2 ^ j 个数) 
 * dp[i][j] = min{dp[i][j-1], dp[i+2^(j-1)][j-1]} 
 * 查询 rmq(s, v) 或 rmqIndex(s, v, b), 查询区间为 [s, v]
 * 将 s - v 分成两个 2 ^ k 的区间 
 * 即 k = (int)log2(s-v+1) 
 * 查询结果应该为 min(dp[s][k], dp[v-2^k+1][k]) 
 */
#define M 100010
#define MAXN 500
#define MAXM 500
int dp[M][18];
void makermq(int n, int b[]) // 返回最小值模式
{
    int i, j;
    for (i = 0; i < n; i++)
        dp[i][0] = b[i];
    for (j = 1; (1 << j) <= n; j++)
        for (i = 0; i + (1 << j) - 1 < n; i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int rmq(int s, int v) // 求最小值
{
    int k = (int)(log((v - s + 1) * 1.0) / log(2.0));
    return min(dp[s][k], dp[v - (1 << k) + 1][k]);
}

void makeRmqIndex(int n, int b[]) //返回最小值对应的下标模式
{
    int i, j;
    for (i = 0; i < n; i++)
        dp[i][0] = i;
    for (j = 1; (1 << j) <= n; j++)
        for (i = 0; i + (1 << j) - 1 < n; i++)
            dp[i][j] = b[dp[i][j - 1]] < b[dp[i + (1 << (j - 1))][j - 1]] ? dp[i][j - 1] : dp[i + (1 << (j - 1))][j - 1];
}
int rmqIndex(int s, int v, int b[]) // 返回最小值对应的下标
{
    int k = (int)(log((v - s + 1) * 1.0) / log(2.0));
    return b[dp[s][k]] < b[dp[v - (1 << k) + 1][k]] ? dp[s][k] : dp[v - (1 << k) + 1][k];
}