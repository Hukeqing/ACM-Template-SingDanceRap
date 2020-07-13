/*
 * Born_Kerbosch 算法
 * 点的编号从 1 开始
 * 先把边情况保存在 mp 数组中
 * 然后使用函数 init()
 * 然后调用 dfs(1, 0, 点数, 0)
 * 答案保存在 ans 中
 */

const int MAXN = "edit";	// 点个数
bool mp[MAXN][MAXN];		// 邻接表
int ans;					// 答案
int done[MAXN][MAXN], notyet[MAXN][MAXN], searched[MAXN][MAXN];

void dfs(int n, int dcnt, int ncnt, int scnt)
{
    if (!ncnt && !scnt)
        ans++;
    if (ans > 1000)
        return;
    int key = notyet[n][1];
    for (int j = 1; j <= ncnt; j++)
    {
        int v = noFtyet[n][j], tmp_ncnt = 0, tmp_scnt = 0;
        if (mp[key][v])
            continue;
        memcpy(done[n + 1], done[n], sizeof(int) * (dcnt + 1));
        done[n + 1][dcnt + 1] = v;
        for (int i = 1; i <= ncnt; i++)
            if (mp[v][notyet[n][i]])
                notyet[n + 1][++tmp_ncnt] = notyet[n][i];
        for (int i = 1; i <= scnt; i++)
            if (mp[v][searched[n][i]])
                searched[n + 1][++tmp_scnt] = searched[n][i];
        dfs(n + 1, dcnt + 1, tmp_ncnt, tmp_scnt);
        notyet[n][j] = 0;
        searched[n][++scnt] = v;
    }
}
void init()
{
    for (int i = 1; i <= n; i++)
        notyet[1][i] = i;
}