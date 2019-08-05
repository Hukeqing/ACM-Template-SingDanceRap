#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = (int) 1e6 + 100;
char str[maxn];
int num[maxn];
ll mod;

struct mat {
    ll m[3][3];

    mat() {
        m[1][1] = m[1][2] = m[2][1] = m[2][2] = 0;
    }

    mat friend operator*(mat a, mat b) {
        mat res;
        for (int k = 1; k <= 2; k++) {
            for (int i = 1; i <= 2; i++) {
                for (int j = 1; j <= 2; j++) {
                    res.m[i][j] += a.m[i][k] * b.m[k][j];
                }
            }
        }

        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= 2; j++) {
                res.m[i][j] %= mod;
            }
        }
        return res;
    }

    mat friend operator^(mat a, int b) {
        mat res;
        res.m[1][1] = res.m[2][2] = 1LL;
        while (b) {
            if (b & 1) {
                res = res * a;
            }
            a = a * a;
            b >>= 1;
        }
        return res;
    }
};

int main(void) {
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b, x1, x2;
    cin >> x1 >> x2 >> a >> b;
    cin >> str >> mod;;

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        num[i] = str[i] - '0';
    }

    num[len - 1]--;
    for (int i = len - 1; i >= 0 && num[i] < 0; i--) {
        num[i] += 10;
        num[i - 1]--;
    }
    mat base, A, ans;
    ans.m[1][1] = ans.m[2][2] = 1;
    base.m[1][1] = a % mod;
    base.m[1][2] = b % mod;
    base.m[2][1] = 1LL;
    A.m[1][1] = x2 % mod;
    A.m[2][1] = x1 % mod;
    for (int i = len - 1; i >= 0; i--) {
        if (num[i]) {
            ans = ans * (base ^ num[i]);
        }
        base = base ^ 10;
    }
    ans = ans * A;
    cout << ans.m[1][1] % mod << endl;
}