map<ll, ll> mp;
inline ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll multi(ll x, ll y, ll mod){
	ll tmp  = x *y - (ll) (((long double)x * y + 0.5)) * mod;
	return tmp < 0 ? tmp + mod : tmp;
}

ll powerMod(ll a, int b, ll m){
	ll res = 1;
	while(b){
		if(b & 1){
			res = res * a % mod;
		}
		b >>= 1;
		a = a * a % mod;
	}
	return res;
}

int main(void){
	ll a, b, m; //a ^ x mod m = b;
	cin >> a >> b >> m;

	ll D = 1, num = 0;
	while(1){
		ll d = gcd(a, m);
		if(d == 1){
			break;
		}
		if(b % d){//b不是d的倍数，无解
			//不存在
		}
		b /= d;
		m /= d;
		num++;
		D = multi(D, a / d, m);
		if(D == b){//系数等于余数，此时x-num为0
			cout << num << endl;
			return;
		}
	}

	ll now = b;//当j=0时，式子右边=b
	mp[now] = 0;
	int mm = ceil(sqrt(m));

	for(int i = 1; i <= mm; i++){
		now = multi(now, a, m);
		mp[now] = i;
	}

	now = D;
	ll q = powerMod(a, mm, m);
	for(int i = 1; i <= mm; i++){
		now = multi(now, q, m);
		if(mp[now]){
			cout << (((ll)i*mm-hash[now]+num)%m+m)%m << endl;
			return;
		}
	}
	cout << "不存在" << endl;
}