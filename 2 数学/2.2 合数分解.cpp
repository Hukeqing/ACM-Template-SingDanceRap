/*
 * 合数分解成素数乘积
 * factor[i][0] 中存储的是素数，factor[i][1] 中存储的是对应的 [0] 有多少个
 * fatCnt 是 facotr 的长度
 * 使用方法：
 * 先 getPrime() 获取素数表
 * 然后使用 getFactor() 来得到表单
 */
const int MAXN = 10000;
int prime[MAXN + 1];
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
long long factor[100][2];
int fatCnt;
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
