#include<bits/stdc++.h>

#define CHAR_NUM 30
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ull ha[NUM], fac[NUM];
ull seed = 131;
char str[NUM];

/**
 *获取哈希值
 */
ull getStr(int l, int r) {
    return ha[r] - ha[l] * fac[r - l];
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < NUM; i++)
        fac[i] = fac[i - 1] * seed;
    while (cin >> str) {
        int size = strlen(str);
        init(size);
        ha[0] = str[0];
        for (int i = 1; i < size; i++)
            ha[i] = ha[i - 1] * seed + str[i];
    }

    return 0;

}