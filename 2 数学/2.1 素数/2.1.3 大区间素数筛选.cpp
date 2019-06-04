/*
 * 给出一个区间 [L,U]，找出区间内容、相邻的距离最近的两个素数和距离最远的两个素数。
 * 1 <= L < U <= 2,147,483,647 区间长度不超过 1,000,000
 * 就是要筛选出 [L,U] 之间的素数
 */
const int MAXN = 100010;            // 把 MAXN 设置为大于 U 的值
int prime[MAXN + 1];
void getPrime() {
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i <= MAXN; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++) {
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
bool notprime[1000010];
int prime2[1000010];
void getPrime2(int L, int R) {
    memset(notprime, false, sizeof(notprime));
    if (L < 2) L = 2;
    for (int i = 1; i <= prime[0] && (long long)prime[i] * prime[i] <= R; i++) {
        int s = L / prime[i] + (L % prime[i] > 0);
        if (s == 1) s = 2;
        for (int j = s; (long long)j * prime[i] <= R; j++)
            if ((long long)j * prime[i] >= L)
                notprime[j * prime[i] - L] = true;
    }
    prime2[0] = 0;
    for (int i = 0;i <= R - L; i++)
        if (!notprime[i])
            prime2[++prime2[0]] = i + L;
}
// L、U 为左右端点，s1、s2 为距离最近的点，f1、f2 为距离最远的点
bool PrimeDistance(int L, int U, int& s1, int& s2, int& f1, int& f2) {
    getPrime();
    getPrime2(L, U);
    if(prime2[0] < 2) return false;
    else {
        s1=0; s2=100000000; f1=0; f2=0;
        for (int i = 1; i < prime2[0]; i++) {
            if(prime2[i + 1] - prime2[i] < s2 - s1) {
                s1 = prime2[i];
                s2 = prime2[i + 1];
            }
            if(prime2[i + 1] - prime2[i] > f2 - f1) {
                f1 = prime2[i];
                f2 = prime2[i + 1];
            }
        }
        return true;
    }
}
