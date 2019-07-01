// Born_Kerbosch 算法(待修正)

const int MAXN = 55;

int some[MAXN][MAXN];
int none[MAXN][MAXN];
int all[MAXN][MAXN];
int mp[MAXN][MAXN];
void dfs(int d, int an, int sn, int nn)
{
	if(!sn && !nn) return;
	for(int i = 0; i < sn; ++i)
	{
		int v = some[d][i];
		for(int j = 0; j < an; ++j)
		all[d+1][j] = all[d][j];
		all[d+1][an] = v;
		int tsn = 0, tnn = 0;
		for(int j = 0; j < sn; ++j)
		if(mp[v][some[d][j]])
		some[d+1][tsn++] = some[d][j];
		for(int j = 0; j < nn; ++j)
		if(mp[v][none[d][j]])
		none[d+1][tnn++] = none[d][j];
		dfs(d+1, an+1, tsn, tnn);
		some[d][i] = 0, none[d][nn++] = v;
	}
}