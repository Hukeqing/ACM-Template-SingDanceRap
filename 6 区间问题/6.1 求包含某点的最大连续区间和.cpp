// 在 i 的位置，最小的连续区间和左端点为 lmin[i]
// 在 i 的位置，最小的连续区间和右端点为 rmin[i]
// 在 i 的位置，最大的连续区间和左端点为 lmin[i]
// 在 i 的位置，最大的连续区间和左端点为 rmin[i]
lmin[1] = 1;
lmax[1] = 1;
rmin[n] = n;
rmax[n] = n;
for (i = 2; i <= n; i++)
{
    if (s[i - 1] - s[lmin[i - 1] - 1] > 0)
        lmin[i] = i;
    else
        lmin[i] = lmin[i - 1];
    if (s[i - 1] - s[lmax[i - 1] - 1] < 0)
        lmax[i] = i;
    else
        lmax[i] = lmax[i - 1];
}
for (i = n - 1; i >= 1; i--)
{
    if (s[rmin[i + 1]] - s[i] > 0)
        rmin[i] = i;
    else
        rmin[i] = rmin[i + 1];
    if (s[rmax[i + 1]] - s[i] < 0)
        rmax[i] = i;
    else
        rmax[i] = rmax[i + 1];
}