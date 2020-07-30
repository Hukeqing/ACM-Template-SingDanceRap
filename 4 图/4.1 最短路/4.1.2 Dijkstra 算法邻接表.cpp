#define INF LONG_LONG_MAX >> 2u              //防止后面溢出，这个不能太大

struct node {
    long long now, d;

    bool operator<(const node &rhs) const {
        return d > rhs.d;
    }
};

priority_queue<node> q;

long long dis[MAXN];
bool vis[MAXN];

void dijkstra(int s, int N, const Graph &graph) {
    for (int i = 0; i <= N; i++) {
        dis[i] = INF;
        vis[i] = 0;
    }

    dis[s] = 0;
    q.push(node{s, dis[s]});
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        int u = p.now;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = graph.head[u], v = graph.edge[i].to; i != -1; i = graph.edge[i].next, v = graph.edge[i].to)
            if (dis[u] + graph.edge[i].cost < dis[v]) {
                dis[v] = dis[u] + graph.edge[i].cost;
                if (!vis[v]) q.push(node{v, dis[v]});
            }
    }
}