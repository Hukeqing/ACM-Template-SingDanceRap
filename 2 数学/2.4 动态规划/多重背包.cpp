/*
玛莎和比尔拥有一系列大理石。他们想要将这些收藏品分开，以便两者都能获得相同份数的弹珠。如果所有的大理石都具有相同的价值，这将很容易，因为那时他们可以将集合分成两半。但不幸的是，一些大理石比其他大理石更大或更漂亮。因此，Marsha和Bill首先为每个大理石分配一个值，即一到六之间的自然数。现在他们想要分割弹珠，使每个弹珠都具有相同的总价值。
不幸的是，他们意识到以这种方式划分弹珠可能是不可能的（即使所有弹珠的总价值是均匀的）。例如，如果有一个值为1的大理石，一个值为3，另一个值为4，则它们不能拆分为相等值的集合。所以，他们要求你写一个程序，检查是否有一个公平的大理石分区
*/

#include<bits/stdc++.h>

using namespace std;

const int maxn = (int) 1e5 + 2000;

int a[7];
int dp[maxn];
int t;

void ZeroOnePack(int c, int w) {
    for (int i = t; i >= c; i--) {
        dp[i] = max(dp[i], dp[i - c] + w);
    }
}

void CompletePack(int c, int w) {
    for (int i = c; i <= t; i++) {
        dp[i] = max(dp[i], dp[i - c] + w);
    }
}

void MultiPack(int c, int w, int am) {
    if (am * c < t) {
        for (int i = 1; i < am;) {
            ZeroOnePack(i * c, i * w);
            am -= 1;
            i <<= 1;
        }
        ZeroOnePack(am * c, am * w);
    } else {
        CompletePack(c, w);
    }
}

int main(void) {
    for (int cal = 1;; cal++) {
        int sum = 0;
        for (int i = 1; i <= 6; i++) {
            cin >> a[i];
            sum += i * a[i];
        }
        if (sum == 0) {
            break;
        }
        printf("Collection #%d:\n",cal);
        if (sum % 2) {
            printf("Can't be divided.\n\n");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        t = sum / 2;
        for (int i = 1; i <= 6; i++) {
            MultiPack(i, i, a[i]);
        }
        if (dp[t] == t) {
            printf("Can be divided.\n\n");
        } else {
            printf("Can't be divided.\n\n");
        }
    }
}