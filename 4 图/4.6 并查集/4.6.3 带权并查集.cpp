/*
 * 带权并查集
 * 权值保存在 dist 中，为相对权值
 * 使用前先 init ，初始化范围为 [b, e)
 * 如果 unions 时发现权值与之前的发生冲突，则会返回 false 并且不赋值
 */

const int MAXN = "Edit";
int dist[MAXN];
int father[MAXN];

void init(int b, int e) {
    for (int i = b; i < e; i++) {
        dist[i] = 0;
        father[i] = i;
    }
}

int finds(int x) {
    if (father[x] == x)
        return x;
    int t = father[x];
    father[x] = finds(father[x]);
    dist[x] += dist[t];
    return father[x];
}

bool unions(int a, int b, int distance) {
    int ra = finds(a);
    int rb = finds(b);
    if (ra == rb && dist[b] - dist[a] != distance)
        return false;
    father[rb] = ra;
    dist[rb] = dist[a] + distance - dist[b];
    return true;
}