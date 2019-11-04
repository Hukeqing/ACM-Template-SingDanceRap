// 0 <= n <= 1e9, 0 <= m <= 1e4, 1 <= k <= 1e9 + 7

vector<int> v;
int dp[110];
ll Cal(int l, int r, int k, int dis){
	ll res = 1;
	for(int i = l; i <= r; i++){
		int t = i;
		for(int j = 0; j < v.size(); j++){
			int y = v[j];
			while(t % y == 0) dp[j] += dis, t /= y;
		}
		res = res * (ll) t % k;
	}
	return res;
}

ll Comb(int n, int m, int k){
	memset(dp, 0, sizeof(dp));
	v.clear();
	int tmp = k;
	for(int i = 2; i * i <= tmp; i++){
		if(tmp % i == 0){
			int num = 0;
			while(tmp % i == 0)	tmp /= i, num++;
			v.push_back(i);
		}
	}
	if(tmp != 1)	v.push_back(tmp);
	ll ans = Cal(n - m + 1, n, k, 1);
	for(int j = 0; j < v.size(); j++)ans = ans * powMod(v[j], dp[j], k) % k;
	ans = ans * inv(Cal(2, m, k, -1), k) % k; //inv是求逆元函数
	return ans;
}
