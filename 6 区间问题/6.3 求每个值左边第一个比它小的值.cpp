/*
 * 求区间中每个值左端第一个严格比它小的值的下标
 * 结果保存在 minl 中
 * 可根据注释修改，记得改变量名，否则容易弄混
 */

#define MAXN 100000
#define type int

stack<int> maxtop;
int minl[MAXN];
void min_left(type *a, int b, int e)
{
    // for (int i = b; i < e; i++)  // 求右端点
    for (int i = e - 1; i >= b; i--)
    {
        // while (!maxtop.empty() && a[maxtop.top()] >= a[i])   // 求小于等于的值的下标
        // while (!maxtop.empty() && a[maxtop.top()] < a[i])    // 求大于的值的下标
        while (!maxtop.empty() && a[maxtop.top()] > a[i])
        {
            minl[maxtop.top()] = i;
            maxtop.pop();
        }
        maxtop.push(i);
    }
    while (!maxtop.empty())
    {
        minl[maxtop.top()] = b - 1;
        maxtop.pop();
    }
}