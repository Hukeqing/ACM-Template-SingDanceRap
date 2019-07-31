/*
 * 1=(001)      C[1]=A[1];
 * 2=(010)      C[2]=A[1]+A[2];
 * 3=(011)      C[3]=A[3];
 * 4=(100)      C[4]=A[1]+A[2]+A[3]+A[4];
 * 5=(101)      C[5]=A[5];
 * 6=(110)      C[6]=A[5]+A[6];
 * 7=(111)      C[7]=A[7];
 * 8=(1000)     C[8]=A[1]+A[2]+A[3]+A[4]+A[5]+A[6]+A[7]+A[8];
 */
const int MAXN = 10010;

int C[MAXN];

// 求出最低位为1的值
int lowbit(int t)
{
    return t & (-t);
}
// 区间求和
int sum(int x)
{
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
        ans += C[i];
    return ans；
}
// 单点修改 增加y
void add(int x, int y)
{
    for (int i = x; i <= n; i += lowbit(i))
        tree[i] += y;
}