/*
 * 1. 当n,m都很小的时候可以利用杨辉三角直接求。
 * C(n, m) = C(n-1, m) + C(n-1, m-1)
 * 2. 利用乘法逆元
 * 组合数答案即 (n!)%mod*inv(m!*(n-m)!)%mod
 * 此模板为方法 2
 * 先 init() 获取阶乘表和逆元表
 * 然后调用函数 C 来得到答案，参数前者在下，后者在上，前者大于等于后者
 */

typedef long long ll;
#define MAXN 10000
#define mod (int)(1e9 + 7)
ll powmod(ll a, ll b)
{
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for (; b; b >>= 1)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

ll inv[MAXN];
void getInv(const int &maxx)
{
    inv[0] = 1;
    inv[maxx] = powmod(fac[maxx], mod - 2);
    for (int i = maxx - 1; i >= 1; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
}

ll fac[MAXN];
void getFac(const int &maxx)
{
    fac[0] = 1;
    for (int i = 1, i < maxx + 1; i++)
        fac[i] = fac[i - 1] * i % mod;
}

ll C(ll n, ll m)
{
    if (m < 0 || n < m)
        return 0;
    if (m > n - m)
        m = n - m;
    return fac[n] * inv[n - m] % mod * inv[m] % mod;
}
void init(int n)
{
    getFac(n);
    getInv(n);
}