//p为模数
struct node{
    ll p, d;
};

ll w;

ll quickMod(ll a, ll b, ll m){
    ll ans = 1;
    a %= m;
    while(b){
        if(b & 1){
            ans = ans * a % m;
        }
        b >>= 1;
        a = a * a % m;
    }
    return ans;
}

//二次域乘法
node multi_er(node a, node b, ll m){
    node ans;
    ans.p = (a.p * b.p % m + a.d * b.d % m * w % m) % m;
    ans.d = (a.p * b.d % m + a.d * b.p % m) % m;
    return ans;
}

//二次域上快速幂
node power(node a, ll b, ll m){
    node ans;
    ans.p = 1;
    ans.d = 0;
    while(b){
        if(b & 1){
            ans = multi_er(ans, a, m);
        }
        b >>= 1;
        a = multi_er(a, a, m);
    }
    return ans;
}

//求勒让德符号
ll legendre(ll a, ll p){
    return quickMod(a, (p - 1) >> 1, p);
}

ll mod(ll a, ll m){
    a %= m;
    return a < 0 ? a + m : a;
}

ll solve(ll n, ll p){
    if(p == 2){
        return 1;
    }
    if(legendre(n, p) + 1 == p){
        return -1;
    }
    ll a = -1, t;
    while(1){
        a = rand() % p;
        t = a * a - n;
        w = mod(t, p);
        if(legendre(w, p) + 1 == p){
            break;
        }
    }

    node tmp;
    tmp.p = a;
    tmp.d = 1;
    node ans = power(tmp, (p + 1) >> 1, p);
    return ans.p;
}

int main(void) {
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while(T--){
        int n, p;
        cin >> n >> p;
        n %= p;
        int a = solve(n, p);
        if(a == -1){
            cout << "No root" << endl;
            continue;
        }
        int b = p - a;
        if(a > n){
            swap(a, b);
        }
        if(a == b){
            cout << a << endl;
        }else{
            cout << a << ' ' << b << endl;
        }
    }
}