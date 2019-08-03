// 标准快速幂
ll pow_mod(ll a, ll b, ll mod)
{
	ll ans = 1, buff = a;
	while (b)
	{
		if (b & 1)
			ans = (ans * buff) % mod;
		buff = (buff * buff) % mod;
		b >>= 1;
	}
	return ans;
}
// 爆 long long 时用的快速幂
ll mod_mul(ll a, ll b, ll n)
{
	ll res = 0;
	while (b)
	{
		if (b & 1)
			res = (res + a) % n;
		a = (a + a) % n;
		b >>= 1;
	}
	return res;
}

ll pow_mod(ll a, ll b, ll n)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			res = mod_mul(res, a, n);
		a = mod_mul(a, a, n);
		b >>= 1;
	}
	return res;
}