/*
 * 素数筛选，求小于等于 MAXN 的数个数。
 * prime[0] 存的是素数的个数
 */
const int MAXN = 10000;
int prime[MAXN + 1];
void getPrime()
{
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i <= MAXN; i++)
    {
        if (!prime[i])
            prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++)
        {
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
