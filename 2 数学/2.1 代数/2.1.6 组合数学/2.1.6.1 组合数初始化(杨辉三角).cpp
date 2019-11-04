// 0 <= m <= n <= 1000

const int maxn = 1010;
ll C[maxn][maxn];
void CalComb(){
	C[0][0] = 1;
	for(int i = 1; i < maxn; i++){
		C[i][0] = 1;
		for(int j = 1; j <= i; j++){
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
}