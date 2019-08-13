#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll x, m, M, r, y, z;
int n;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void inv(ll a, ll b) {
    if (a % b == 0) {
        z = 0;
        y = 1;
        return;
    }
    inv(b, a % b);
    ll r = z;
    z = y;
    y = r - a / b * y;
}

void solve() {
    x = 0;
    m = 1;
    for (int i = 0; i < n; i++) {
        cin >> M >> r;
        ll b = r - x, d = gcd(m, M);
        if (b % d) {
            cout << "-1" << endl;//不存在
            return;
        }
        inv(m / d, M / d);
        ll t = b / d * z % (M / d);
        x += m * t;
        m *= M / d;
    }
    x = x > 0 ? x : x + m;
    cout << x << endl;
}