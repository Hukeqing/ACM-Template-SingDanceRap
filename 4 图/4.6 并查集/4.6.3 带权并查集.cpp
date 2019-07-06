/*
 * 带权并查集
 * 权值保存在 dist 中，为相对权值
 * 使用前先 init ，初始化范围为 [b, e)
 * 如果 unions 时发现权值与之前的发生冲突，则会返回 false 并且不赋值
 */
typedef long long ll;

const int MAXN = 100000 + 10;
ll dist[MAXN];
ll father[MAXN];

void init(ll b, ll e)
{
    for (ll i = b; i < e; i++)
    {
        dist[i] = 0;
        father[i] = i;
    }
}
ll finds(ll x)
{
    if (father[x] == x)
        return x;
    ll t = father[x];
    father[x] = finds(father[x]);
    dist[x] += dist[t];
    return father[x];
}
bool unions(ll a, ll b, ll distance)
{
    ll ra = finds(a);
    ll rb = finds(b);
    if (ra == rb && dist[b] - dist[a] != distance)
        return false;
    father[rb] = ra;
    dist[rb] = dist[a] + distance - dist[b];
    return true;
}