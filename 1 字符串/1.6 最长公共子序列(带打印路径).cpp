const int maxn = 10000;

int dp[maxn][maxn];
char c;

int main(void) {
    char a[maxn], b[maxn];

    cin >> a >> b;
    int la = strlen(a), lb = strlen(b);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            if (a[i - 1] == b[j - 1]){
                dp[1][j] = dp[i - 1][j - 1] + 1;
            }else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int i = la, j = lb;
    stack<char> s;
    while(dp[i][j]){
        if(dp[i][j] == dp[i - 1][j]){
            i--;
        }else if(dp[i][j] == dp[i][j - 1]){
            j--;
        }else if(dp[i][j] > dp[i - 1][j - 1]){
            i--;
            j--;
            s.push(a[i]);
        }
    }
    while(!s.empty()){
        c = s.top();
        cout << c;
        s.pop();
    }
}