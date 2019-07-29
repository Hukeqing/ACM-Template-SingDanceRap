// 数组 a 保存值，数组 s 为前缀和(函数自带)，下标对应
// 在 i 的位置，最小的连续区间和左端点为 lmin[i]
// 在 i 的位置，最小的连续区间和右端点为 rmin[i]
// 在 i 的位置，最大的连续区间和左端点为 lmax[i]
// 在 i 的位置，最大的连续区间和左端点为 rmax[i]
// 即包含 i 的和最大连续区间为 [lmax[i], rmax[i]]，此时的和为 s[rmax[i]] - s[lmax[i] - 1]
#define MAXN (int)(3e6 + 100)
#define type int // 当前缀和可能出现大于 int 时修改为 long long

type s[MAXN];
int lmin[MAXN], rmin[MAXN];
int lmax[MAXN], rmax[MAXN];

void solve(type *a, int b, int e) // 计算区间 [b, e)
{
    lmin[b] = b;
    rmin[e - 1] = e - 1;
    lmax[b] = b;
    rmax[e - 1] = e - 1;
    s[b] = a[b];
    for (int i = b + 1; i < e; i++)
    {
        s[i] = s[i - 1] + a[i]; // 前缀和
        if (s[i - 1] - s[lmin[i - 1] - 1] > 0)
            lmin[i] = i;
        else
            lmin[i] = lmin[i - 1];
        if (s[rmin[e + b - i]] - s[e + b - i - 1] > 0)
            rmin[e + b - i - 1] = e + b - i - 1;
        else
            rmin[e + b - i - 1] = rmin[e + b - i];
        if (s[i - 1] - s[lmax[i - 1] - 1] < 0)
            lmax[i] = i;
        else
            lmax[i] = lmax[i - 1];
        if (s[rmax[e + b - i]] - s[e + b - i - 1] < 0)
            rmax[e + b - i - 1] = e + b - i - 1;
        else
            rmax[e + b - i - 1] = rmax[e + b - i];
    }
}