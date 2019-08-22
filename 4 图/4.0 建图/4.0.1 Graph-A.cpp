/*
 * 邻接表结构
 * 仅保存图结构
 */
#define MAXN 2000
#define MAXM 10000

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