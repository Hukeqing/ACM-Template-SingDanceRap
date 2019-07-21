int pow_mod(int a, int n, int mod)
{
    if(n == 0) return 1;
    int x = pow_mod(a, n/2, mod);
    long long ans = (long long)x * x % mod;
    if(n % 2 == 1) ans = ans *a % mod;
    return (int)ans;
}