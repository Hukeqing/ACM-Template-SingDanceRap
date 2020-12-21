#include<bits/stdc++.h>

#define NUM 600000
using namespace std;

typedef unsigned long long ull;

ull ha[NUM], fac[NUM];
ull seed = 201326611;// 201326611 233 50331653 212370440130137957ll
char str[NUM];

/**
 * 获取子串[l, r]（均为闭区间）的哈希值
 */
ull getStr(int l, int r) {
    if (l == 0)
        return ha[r];
    return ha[r] - ha[l - 1] * fac[r - l + 1];
}

int main() {
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    fac[0] = 1;
    for (int i = 1; i < NUM; i++)
        fac[i] = fac[i - 1] * seed;
    cin >> str;
    int size = strlen(str);
    ha[0] = str[0];
    for (int i = 1; i < size; i++)
        ha[i] = ha[i - 1] * seed + str[i];
    return 0;
}
