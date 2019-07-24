const int MAXN = 31; //如果为 long long 则改成 63 即可
int d[MAXN + 5];
void init()
{
    memset(d, 0, sizeof(d));
}
void add(int x)
{
    for (int i = MAXN; i >= 0; i--)
    {
        if (x & (1LL << i))
        {
            if (d[i])
                x ^= d[i];
            else
            {
                d[i] = x;
                break;
            }
        }
    }
}
// 如何求异或后第k小的值
void work() //处理线性基
{
    for (int i = 1; i <= 60; i++)
        for (int j = 1; j <= i; j++)
            if (d[i] & (1 << (j - 1)))
                d[i] ^= d[j - 1];
}
ll k_th(ll k)
{
    if (k == 1 && tot < n)
        return 0; //特判一下，假如k=1，并且原来的序列可以异或出0，就要返回0，tot表示线性基中的元素个数，n表示序列长度
    if (tot < n)
        k--; //类似上面，去掉0的情况，因为线性基中只能异或出不为0的解
    work();
    ll ans = 0;
    for (int i = 0; i <= 60; i++)
        if (d[i] != 0)
        {
            if (k % 2 == 1)
                ans ^= d[i];
            k /= 2;
        }
}
