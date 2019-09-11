/*
 * Miller-Rabin 算法判断素性
 * 调用函数 isprime 即可判断素性
 * 板子中使用了 ll * ll 的情况，如果爆 ll 请用下方注释的代码代替原来的 pow_mod 函数
 * 函数的复杂度为 log(2)N * C，C为常数等于下面你选择的数组长度*快速幂复杂度，计算一次 1e16 约需要 1e4 的复杂度
ll mod_mul(ll a, ll b, ll n) {
    ll res = 0;
    while (b) {
        if(b & 1)
            res = (res + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return res;
}

ll pow_mod(ll a, ll b, ll n) {
    ll res = 1;
    while(b) {
        if(b & 1)
            res = mod_mul(res, a, n);
        a = mod_mul(a, a, n);
        b >>= 1;
    }
    return res;
}
 */
typedef unsigned long long ll;

ll pow_mod(ll a, ll b, ll r)
{
	ll ans = 1, buff = a;
	while (b)
	{
		if (b & 1)
			ans = (ans * buff) % r;
		buff = (buff * buff) % r;
		b >>= 1;
	}
	return ans;
}

bool test(ll n, ll a, ll d)
{
	if (n == 2)
		return true;
	if (n == a)
		return false;
	if (!(n & 1))
		return false;
	while (!(d & 1))
		d >>= 1;
	ll t = pow_mod(a, d, n);
	while (d != n - 1 && t != n - 1 && t != 1)
	{
		t = t * t % n; //下面介绍防止溢出的办法，对应数据量为10^18次方；
		d <<= 1;
	}
	return t == n - 1 || (d & 1) == 1; //要么t能变成n-1，要么一开始t就等于1
}
bool isprime(ll n)
{
	// 下面三个数组根据情况选择一个使用，复杂度为后两者比较接近
	// 如果使用了最后一种素数判定方法，记得特判 46856248255981 不是素数
	int a[3] = {2, 7, 61};				 // 精度：4e10，最小伪素数：4'759'123'141
	int a[7] = {2, 3, 5, 7, 11, 13, 17}; // 精度：3e15，最小伪素数：341'550'071'728'320
	int a[5] = {2, 3, 7, 61, 24251};	 // 精度：1e16，唯一在此范围内的伪素数：46'856'248'255'981
	// 将下方的循环中的 5 改成上面的长度
	for (int i = 0; i < 5; ++i)
	{
		if (n == a[i])
			return true;
		if (!test(n, a[i], n - 1))
			return false;
	}
	return true;
}