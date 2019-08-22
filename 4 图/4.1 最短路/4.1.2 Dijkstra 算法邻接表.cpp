/*
 * 单源最短路径，Dijkstra 算法，邻接表形式，使用 Graph-B，复杂度为O(n^2)
 * 求出源 start 到所有点的最短路径, 路径权值必须非负
 * 各点的最短路径保存在 lowcost[], pre[i] -> i 的路必选, pre[start] = -1
 * 直接调用 solve 函数求解，点编号范围为 [b, e)，start为起点，graph使用 Graph-B 类型
 * 调用 get_road 函数获取最短路径，将逆序保存在数组 road 中
 */

#define INF 0x3fffffff              //防止后面溢出，这个不能太大

struct Dijkstra {
    int low_cost[MAXN];
    bool vis[MAXN];
    int pre[MAXN];

    void solve(int b, int e, int start, Graph &graph) {
        for (int i = b; i < e; i++) {
            low_cost[i] = INF;
            vis[i] = false;
            pre[i] = -1;
        }
        low_cost[start] = 0;
        vis[start] = true;
        int cur_edge = graph.head[start];
        while (cur_edge != -1) {
            if (!vis[graph.edge[cur_edge].to] &&
                low_cost[start] + graph.edge[cur_edge].cost < low_cost[graph.edge[cur_edge].to]) {
                low_cost[graph.edge[cur_edge].to] = low_cost[start] + graph.edge[cur_edge].cost;
                pre[graph.edge[cur_edge].to] = start;
            }
            cur_edge = graph.edge[cur_edge].next;
        }
        for (int j = b; j < e - 1; j++) {
            int k = -1;
            int Min = INF;
            for (int i = b; i < e; i++) {
                if (!vis[i] && low_cost[i] < Min) {
                    Min = low_cost[i];
                    k = i;
                }
            }
            if (k == -1)
                break;
            vis[k] = true;
            cur_edge = graph.head[k];
            while (cur_edge != -1) {
                if (!vis[graph.edge[cur_edge].to] &&
                    low_cost[k] + graph.edge[cur_edge].cost < low_cost[graph.edge[cur_edge].to]) {
                    low_cost[graph.edge[cur_edge].to] = low_cost[k] + graph.edge[cur_edge].cost;
                    pre[graph.edge[cur_edge].to] = k;
                }
                cur_edge = graph.edge[cur_edge].next;
            }
        }
    }

    int get_road(int n, int *road) {
        int cur_node = n;
        int cnt = 0;
        while (cur_node != -1) {
            road[cnt++] = cur_node;
            cur_node = pre[cur_node];
        }
        return cnt;
    }
};