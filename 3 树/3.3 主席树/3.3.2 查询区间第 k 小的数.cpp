/*
 * 主席树求区间第 k 小，支持离线查询
 * 先将变量保存至数组 a 中，点编号为 1 - n
 * 然后调用 Init_hash 函数完成建树
 * 之后便可以进行询问操作
 * 重复数字会重复结算
 */
const int MAXN = 100010;
const int M = MAXN * 30;
int n, q, m, tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int build(int l, int r)
{
    int root = tot++;
    c[root] = 0;
    if (l != r)
    {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
int myhash(int x)
{
    return lower_bound(t + 1, t + 1 + m, x) - t;
}
int update(int root, int pos, int val)
{
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = m;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (pos <= mid)
        {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int query(int left_root, int right_root, int k) // 参数为左区间、右区间、第 k 小，区间两端为闭区间
{
    int l = 1, r = m;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (c[lson[left_root]] - c[lson[right_root]] >= k)
        {
            r = mid;
            left_root = lson[left_root];
            right_root = lson[right_root];
        }
        else
        {
            l = mid + 1;
            k -= c[lson[left_root]] - c[lson[right_root]];
            left_root = rson[left_root];
            right_root = rson[right_root];
        }
    }
    return l;
}
void Init_hash()
{
    for (int i = 1; i <= n; i++)
        t[i] = a[i];
    sort(t + 1, t + 1 + n);
    m = unique(t + 1, t + 1 + n) - t - 1;
    T[n + 1] = build(1, m);
    for (int i = n; i; i--)
    {
        int pos = myhash(a[i]);
        T[i] = update(T[i + 1], pos, 1);
    }
}