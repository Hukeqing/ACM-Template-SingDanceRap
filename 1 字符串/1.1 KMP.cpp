/*
 * next[] 的含义:x[i-next[i]...i-1]=x[0...next[i]-1]
 * next[i] 为满足 x[i-z...i-1]=x[0...z-1] 的最大 z 值(就是 x 的自身匹配)
 */
void kmp_pre(char *x, int m, int *next)
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < m)
    {
        while (-1 != j && x[i] != x[j])
            j = next[j];
        next[++i] = ++j;
    }
}
/*
 * kmpNext[i] 的意思:next'[i]=next[next[...[next[i]]]](直到 next'[i]<0 或者 x[next'[i]]!=x[i])
 * 这样预处理可以快一点
 */
void preKMP(char *x, int m, int *kmpNext)
{
    int i = 0, j = kmpNext[0] = -1;
    while (i < m)
    {
        while (-1 != j && x[i] != x[j])
            j = kmpNext[j];
        if (x[++i] == x[++j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}
/*
 * 以上两个预处理的函数均可用，且效果相同
 */
int KMP_Count_Unoverlap(char *x, int m, char *y, int n)
{ //x 是模式串，y 是主串，m 为 x 的长度，n 为 y 的长度，返回 x 在 y 中出现的次数，不可以重叠
    int cnt = 0, k = -1;
    int *next = new int[m + 5];
    kmp_pre(x, m, next);
    //    preKMP(x, m, next);
    for (int i = 0; i < n; i++)
    {
        while (k > -1 && x[k + 1] != y[i])
            k = next[k];
        if (x[k + 1] == y[i])
            k++;
        if (k == m - 1)
        {
            k = -1;
            cnt++;
        }
    }
    delete[] next;
    return cnt;
}
int KMP_Count_Overlap(char *x, int m, char *y, int n)
{ //x 是模式串，y 是主串，m 为 x 的长度，n 为 y 的长度，返回 x 在 y 中出现的次数，可以重叠
    int i = 0, j = 0, ans = 0;
    int *next = new int[m + 5];
    kmp_pre(x, m, next);
    //    preKMP(x, m, next);
    while (i < n)
    {
        while (-1 != j && y[i] != x[j])
            j = next[j];
        i++;
        j++;
        if (j >= m)
        {
            ans++;
            j = next[j];
        }
    }
    delete[] next;
    return ans;
}
