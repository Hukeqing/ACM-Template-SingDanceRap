//求解组合数取模p，其中p为质数
//求解逆元
ll powMod(ll a, ll b, ll p){
	ll ret = 1;
	while(b){
		if(b & 1){
			ret = ret * a % mod;
		}
		b >>= 1;
		a = a * a % p;
	}
	return ret;
}

//求组合数，因为分解得较小了，所以可以用暴力
ll C(ll n, ll m, ll p){
	if(m > n){
		return 0;
	}
	ll c1 = 1, c2 = 1;
	for(int i = n + m - 1; i <= n; i++){
		c1 = c1 * i % p;
	}
	for(int i = 2; i <= m; i++){
		c2 = c2 * i % p;
	}

	return c1 * powMod(c2, p - 2, p) % p;
}

ll lucas(ll n, ll m, ll p){
	if(!m)	return 1;
	return C(n % p, m %p, p) * lucas(n / p, m / p, p) * p;
}