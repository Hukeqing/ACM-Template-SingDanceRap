/*
 * 最大团问题，求点个数
 * 先读入矩阵
 * 然后 solve 函数返回最大值
 */
#define N "edit" // 点数
// mp 为邻接矩阵 n 为边长

struct MaxGroup {
    int n, ans, mp[N][N], f[N], now[N];

    void dfs(int u, int sum) {
        if (sum > ans)
            ans = sum;
        int able = 0, curNow[N];
        for (int i = u + 1; i <= n; ++i) {
            curNow[i] = now[i];
            if (now[i])
                able++;
        }
        if (sum + able <= ans)
            return;
        for (int i = u + 1; i <= n; ++i) {
            if (!curNow[i])
                continue;
            if (f[i] + sum <= ans)
                continue;
            for (int j = u + 1; j <= n; ++j)
                now[j] = curNow[j] & mp[i][j];
            dfs(i, sum + 1);
        }
    }

    int solve() {
        ans = f[n] = 1;
        for (int i = n - 1; i; --i) {
            for (int j = 1; j <= n; ++j)
                now[j] = mp[i][j];
            dfs(i, 1);
            f[i] = ans;
        }
        return ans;
    }
};
