int solve(int n, int W) {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) { //i从1开始，因为i=0的值已经确定为0
        for (int j = 0; j <= W; j++) {
            if (j < w[i]) {
                dp[i][j] = dp[i-1][j];
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]);//v是价值，w是花费
            }
        }
    }
    return dp[n][W];
}
