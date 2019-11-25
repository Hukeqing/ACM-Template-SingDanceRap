//用树状数组的方法求逆序对
ll num[maxn], b[maxn], c[maxn];	//b用于正序的中间数组，c用于反序的中间数组
ll ans;
int n;
int lowbit(int x){
    return x & (-x);
}

void add(ll a[], ll pos, ll val){
    while(pos <= maxn){
        a[pos] += val;
        pos += lowbit(pos);
    }
}

ll sum(ll a[], ll pos){//求逆序对的个数
    ll tmp = 0;
    while(pos > 0){
        tmp += a[pos];
        pos -= lowbit(pos);
    }
    return tmp;
}

int main(void) {
    while(cin >> n){
        memset(c, 0, sizeof(ll) * (n +5));
        memset(b, 0, sizeof(ll) * (n + 5));
        ans = 0;
        //这是求逆序对的和，若求逆序对的个数只要一个for循环就可
        for(int i = 1; i <= n; i++){
            cin >> num[i];
            add(c, num[i], 1);
            //逆序对的个数
            //ans += sum(c, num[i]);
            ans += num[i] * (i - sum(c, num[i]));
        }
        for(int i = n; i >= 1; i--){
            ans += num[i] * (sum(b, num[i]));
            add(b, num[i], 1);
        }
        cout << ans << endl;
    }
}