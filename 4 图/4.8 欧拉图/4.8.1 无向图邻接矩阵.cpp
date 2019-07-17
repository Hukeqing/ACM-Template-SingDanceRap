/*
 * 欧拉图邻接矩阵找字典序最小的路径
 * MAXN 为最大点数
 * 使用 init 函数进行初始化
 * 用 addedge 函数增加边
 * 用 check 函数求得是否存在欧拉路径
 * 用 getroad 函数求得路径，保存在 ans 中(起点除外)
 */
#define MAXN 60
typedef pair<bool, bool> PBB;

PBB edge[MAXN][MAXN];
bool live[MAXN];
int d[MAXN];
stack<int> ans;

void init(int b, int e)
{
    for (int i = b; i < e; i++)
    {
        for (int j = b; j < e; j++)
            edge[i][j] = make_pair(false, false);
        d[i] = 0;
        live[i] = false;
    }
}

void addedge(int u, int v)
{
    edge[u][v].first = true;
    edge[v][u].first = true;
    d[u]++;
    d[v]++;
    live[u] = true;
    live[v] = true;
}

int check(int b, int e)     // 是否为欧拉图， b、e 为点的范围 [b, e)
{
    int cnt = 0, start = MAXN, minodd = MAXN;
    for (int i = b; i < e; i++)
    {
        if (!live[i])
            continue;
        if (d[i] & 1)
        {
            cnt++;
            if (cnt > 2)
                break;
            minodd = min(minodd, i);
        }
        start = min(start, i);
    }
    if (cnt == 0)
        return start;
    else if (cnt == 2)
        return minodd;
    return -1;
}
void getroad(int b, int e, int start)         // 欧拉路径， b、e 为点的范围 [b, e)，start 为起点
{
    for (int i = b; i < e; i++)
    {
        if (edge[start][i].first && !edge[start][i].second)
        {
            edge[start][i].second = true;
            edge[i][start].second = true;
            getroad(b, e, i);
            ans.push(i);
        }
    }
}