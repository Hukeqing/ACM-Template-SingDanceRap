// 0 <= m <= n <= 1e5, 模p为质数

const int maxn = 100010;
ll f[maxn];
ll inv[maxn]; //阶乘的逆元
void CalFact(){
	f[0] = 1;
	for(int i = 1; i < maxn; i++){
		f[i] = (f[i - 1] * i) % p;
	}
	inv[maxn - 1] = powMod(f[maxn - 1], p - 2, p);
	for(int i = maxn - 2; ~i; i--){
		inv[i] = inv[i +1] * (i + 1) % p;
	}
}

ll C(int n, int m){
	return f[n] * inv[m] % p * inv[n - m] % p;
}