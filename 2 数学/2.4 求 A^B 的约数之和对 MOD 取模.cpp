const int MOD = 1e9 + 7;
const int MAXN = 10000;
int prime[MAXN + 1];
long long factor[100][2];
int fatCnt;

void getPrime() {
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i <= MAXN; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++) {
            prime[prime[j] * i] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
int getFactors(long long x) {
    fatCnt = 0;
    long long tmp = x;
    for (int i = 1; prime[i] <= tmp / prime[i]; i++) {
        factor[fatCnt][1] = 0;
        if (tmp % prime[i] == 0) {
            factor[fatCnt][0] = prime[i];
            while (tmp % prime[i] == 0) {
                factor[fatCnt][1]++;
                tmp /= prime[i];
            }
            fatCnt++;
        }
    }
    if (tmp != 1) {
        factor[fatCnt][0] = tmp;
        factor[fatCnt++][1] = 1;
    }
    return fatCnt;
}

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
// 计算1+p+p^2+...+p^n
long long sum(long long p, long long n) {
    if (p == 0) return 0;
    if (n == 0) return 1;
    if (n & 1) return ((1 + pow_m(p, n / 2 + 1)) % MOD * sum(p, n / 2) % MOD) % MOD;
    else return ((1 + pow_m(p, n / 2 + 1)) % MOD * sum(p, n / 2 - 1) + pow_m(p, n / 2) % MOD) % MOD;
}
// 返回 A^B 的约数之和 % MOD
long long solve(long long A, long long B) {
    getFactors(A);
    long long ans = 1;
    for (int i = 0; i < fatCnt; i++) {
        ans *= sum(factor[i][0],B * factor[i][1]) % MOD;
        ans %= MOD;
    }
    return ans;
}
