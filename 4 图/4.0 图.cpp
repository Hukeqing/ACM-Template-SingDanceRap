#define MAXN 2000
#define MAXM 10000
// 无权有向图
struct Graph {
    struct Edge {
        int to, next;
    } edge[MAXM];
    int head[MAXN];
    int tot;

    void init(int n) {
        tot = 0;
        memset(head, -1, sizeof(int) * (n + 1));
    }

    void add_edge(int from, int to) {
        edge[tot].to = to;
        edge[tot].next = head[from];
        head[from] = tot++;
    }
};
// 权值有向图
struct Graph {
    struct Edge {
        int to, next;
        int cost;
    } edge[MAXM];
    int head[MAXN];
    int tot;

    void init(int n) {
        tot = 0;
        memset(head, -1, sizeof(int) * (n + 1));
    }

    void add_edge(int from, int to, int value) {
        edge[tot].to = to;
        edge[tot].cost = value;
        edge[tot].next = head[from];
        head[from] = tot++;
    }
};
// 最大流专用图
struct Graph {
    struct Edge {
        int to, next;
        int cap;
        int flow;
    } edge[MAXM];
    int head[MAXN];
    int tot;

    void init(int n) {
        tot = 0;
        memset(head, -1, sizeof(int) * (n + 1));
    }

    void add_edge(int from, int to, int value, int rvalue = 0) {
        edge[tot].to = to;
        edge[tot].cap = value;
        edge[tot].flow = 0;
        edge[tot].next = head[from];
        head[from] = tot++;
        edge[tot].to = from;
        edge[tot].cap = rvalue;
        edge[tot].flow = 0;
        edge[tot].next = head[to];
        head[to] = tot++;
    }
};
// 遍历图
void for_edge(Graph &graph, int node) {
    for (int i = graph.head[node]; i != -1; i = graph.edge[i].next);
}
