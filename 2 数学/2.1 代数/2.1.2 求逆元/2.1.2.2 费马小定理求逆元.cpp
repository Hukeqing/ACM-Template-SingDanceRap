/*
 * 费马小定理求逆元
 * 仅当 mod 为素数时可用
 * 调用 inv 函数获取逆元
 */

const int mod = 1000000009;

long long quickpow(long long a, long long b)
{
    if (b < 0)
        return 0;
    long long ret = 1;
    a %= mod;
    while (b)
    {
        if (b & 1)
            ret = (ret * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ret;
}
long long inv(long long a)
{
    return quickpow(a, mod - 2);
}