//F(n) =∑d|n f(d) ⇒ f(n) =∑d|n µ(d)F(n d 
//F(n) =∑n|d f(d) ⇒ f(n) =∑n|d µ( d n)F(d) 

const int maxn = "Edit";
int prime[maxn], tot, mu[maxn];
bool check[maxn];
void CalMu(){
	mu[1] = 1;
	for(int i = 2; i < maxn; i++){
		if(!check[i])	prime[tot++] = i, mu[i] = -1;
		for(int j = 0; j < tot; j++){
			if(i * prime[j] >= maxn)	break;
			check[i * prime[j]] = true;
			if(i % prime[j] == 0){
				mu[i * prime] = 0;
				break;
			}else{
				mu[i * prime[j]] = - mu[i];
			}
		}
	}
}

//Examples
//有n个数(n < 100000, 1 < ai < 1e6)，问这n个数中互质的数的对数

const int maxn = "Edit";
int b[maxn];

ll solve(int n){
	ll ans = 0;
	for(int i = 0, x; i < n; i++){
		cin >> x;
		b[x]++;
	}
	for(int i = 1; i < maxn; i++){
		int cnt = 0;
		for(int j = i; j < maxn; j += i){
			cnt += b[j];
		}
		ans += 1LL * mu[i] * cnt * cnt;
	}
	return (ans - b[1]) / 2;
}

//gcd(x, y) == 1的对数, x <= n, y <= m;

ll solve(int n, int m){
	if(n > m)	swap(n, m);
	ll ans = 0;
	for(int i = 1; i <= n; i++){
		ans += (ll)mu[i] * (n / i) * (m / i);
	}
	return ans;
}