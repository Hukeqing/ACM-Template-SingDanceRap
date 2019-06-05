const int MOD = 1e9 + 7;

long long pow_m(long long a, long long n) {
    long long ret = 1;
    long long tmp = a % MOD;
    while(n) {
        if(n & 1) ret = (ret * tmp) % MOD;
        tmp = tmp * tmp % MOD;
        n >>= 1;
    }
    return ret;
}

// 计算 1 + p + p^2 + ... + p^n MOD 1e9 + 7
long long sum(long long p, long long n) {
    if (p == 0) return 0;
    if (n == 0) return 1;
    if (n & 1) return ((1 + pow_m(p, n / 2 + 1)) % MOD * sum(p, n / 2) % MOD) % MOD;
    else return ((1 + pow_m(p, n / 2 + 1)) % MOD * sum(p, n / 2 - 1) + pow_m(p, n / 2) % MOD) % MOD;
}
