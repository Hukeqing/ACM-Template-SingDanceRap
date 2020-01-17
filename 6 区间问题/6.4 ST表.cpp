/*
 * ST 表，离线 RMQ 问题
 * st[i][j] 表示原数组中 [i, i+2^j-1] 的最小值
 * 预处理效率：O(nlogn)
 * 查询效率：O(1)
 */
int a[1010];//原始输入数组
int st[1010][20];//st表

void init(int n)
{
    for (int i = 0; i < n; i++)
        st[i][0] = a[i];

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
            st[i][j] = min(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
    }
}

int search(int l, int r)
{
    int k = (int)(log((double)(r - l + 1)) / log(2.0));
    return min(st[l][k],st[r - (1 << k) + 1][k]);
}