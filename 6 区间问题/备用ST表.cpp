#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#ifdef ACM_LOCAL
const ll NUM = 2e5 + 10;
#else
const ll NUM = 2e5 + 10;
#endif

struct ST {
    ll STMax[NUM][20], STMin[NUM][20], mn[NUM];

    void initST(int n, const ll *a) {
        mn[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mn[i] = ((i & (i - 1)) == 0) ? mn[i - 1] + 1 : mn[i - 1];
            STMax[i][0] = STMin[i][0] = a[i];
        }
        for (int j = 1; j <= mn[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                STMax[i][j] = max(STMax[i][j - 1], STMax[i + (1 << (j - 1))][j - 1]);
                STMin[i][j] = min(STMin[i][j - 1], STMin[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll rmqMax(int l, int r) {
        int k = mn[r - l + 1];
        return max(STMax[l][k], STMax[r - (1 << k) + 1][k]);
    }

    ll rmqMin(int l, int r) {
        int k = mn[r - l + 1];
        return min(STMin[l][k], STMin[r - (1 << k) + 1][k]);
    }
} st;
