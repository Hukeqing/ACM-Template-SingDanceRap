//s(n, m) = s(n - 1, m - 1) + (n - 1) * s(n - 1, m)
//给定正整数n(1<=n<=20),计算出n个元素的集合{1,2,…,n} 可以化为多少个不同的非空子集。
typedef long long ll;
const int N = 101;
ll s[N][N];

void init(){
    memset(s, 0, sizeof(s));
    s[1][1] = 1;
    for(int i = 2; i < N; i++){
        for(int j = 1; j <= i; j ++){
            s[i][j] = (s[i - 1][j - 1] + (i - 1) * s[i - 1][j]);
        }
    }
}

int main(void){
    init();
    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        ll sum = 1;
        for(ll i = 2; i <= n; i++){
            sum *= i;
        }
        ll fz = 0;
        for(int i = 1; i <= k; i++){
            fz += (s[n][i] - s[n-1][i-1]);
        }
        double ans = fz * 1.0 / sum;
        printf("%.4lf\n", ans);
    }
}