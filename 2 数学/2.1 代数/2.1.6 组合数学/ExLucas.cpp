//求解组合数求模p，且p不一定是质数
ll c[1000006], a[1000005];
ll powMod(ll a, ll b, ll p){
	ll ret = 1;
	while(b){
		if(b & 1)	ret =ret * a % p;
		b >>= 1
		a = a * a % p;
	}
	return ret;
}

//求阶乘
ll fac(ll n, ll p, ll pk){
	if(!n)	return 1;
	ll ans = 1;
	for(int i = 1; i < pk; i++){
		if(i % p)	ans = ans * i % pk;//同余部分
	}
	ans = powMod(ans, n / pk, pk);
	for(int i = 1; i <= n % pk; i++){//剩余无法凑同余的部分
		if(i % p)	ans = ans * i % pk;
	}
	return ans * fac(n / p, p, pk) % pk;
}

ll exgcd(ll a, ll b, ll &x, ll &y){
	if(!b){
		x = 1, y = 0;
		return a;
	}
	ll xx, yy, g = exgcd(b, a % b, xx, yy);
	x = yy;
	y = xx - a / b * yy;
	return g;
}

ll inv(ll a, ll b){ //求逆元
	ll x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}

//求组合数
ll C(ll n, ll m, ll p, ll pk){
	if(m > n)	return 0;
	ll f1 = fac(n, p, pk), f2 = fac(m, p, pk), f3 = fac(n - m, p, pk), cnt = 0;
	for(ll i = n; i; i /= p){
		cnt += i / p;
	}
	for(ll i = m; i; i /= p){
		cnt -= i / p;
	}
	for(ll i = n - m; i; i /= p){
		cnt -= i / p;
	}
	return f1 * inv(f2, pk) % pk * inv(f3, pk) % pk *powMod(p, cnt, pk) % pk;
}

ll CRT(ll cnt){
	ll M = 1, ans = 0;
	for(int i = 1; i <= cnt; i++){
		M *= c[i]; //p的值发生变化，所以要重新计算
	}
	for(int i = 1; i <= cnt; i++){
		ans = (ans + a[i] * (M / c[i]) % M * inv(M / c[i], c[i]) % M) % M;
	}
	return ans;
}

ll exlucas(ll n, ll m, ll p){
	ll temp, cnt = 0;
	for(int i = 2; p > 1 && i <= p / i; i++){
		ll tmp = 1;
		while(p % i == 0){
			p /= i, tmp *= i;
		}
		if(tmp > 1){
			a[++cnt] = C(n, m, i, tmp);
			c[cnt] = tmp;
		}
	}
	if(p > 1){
		c[++cnt] = p, a[cnt] = C(n, m, p, p);
	}
	return CRT(cnt);
}

int main(){
	ll m, n, p;
	cin >> n >> m >> p;
	cout << exlucas(n, m, p);
}