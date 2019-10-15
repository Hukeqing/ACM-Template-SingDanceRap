//引用返回通解：X = x + k * dx, Y = y - k * dy;
//引用返回的x是最小非负整数解，方程无解函数返回0

#define Mod(a, b) (((a) % (b) + (b)) % (b))

ll exgcd(ll a, ll b, ll &x, ll &y){
	ll d = a;
	if(b){
		d = exgcd(b, a % b, y, x);
		y -= x * (a / b);
	}else{
		x = 1;
		y = 0;
	}
	return d;
}

bool solve(ll a, ll b, ll c, ll &x, ll &y, ll &dx, ll &dy){
	if(a == 0 & b == 0){
		return 0;
	}
	ll x0, y0;
	ll d = exgcd(a, b, x0, y0);
	if(c % d != 0)	return 0;
	dx = b / d, dy = a / d;
	x = Mod(x0 * c / d, dx);
	y = (c - a * x) / b;
	return 1;
}