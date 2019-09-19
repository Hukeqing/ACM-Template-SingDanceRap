/*
 * 单源最短路径，SPFA 算法，邻接表形式，复杂度为O(n^2)
 * 求出源 start 到所有点的最短路径, 路径权值可以为负
 * 各点的最短路径保存在 lowcost[], pre[i] -> i 的路必选, pre[start] = -1
 * 直接调用 solve 函数求解，点编号范围为 [b, e)，start为起点，graph使用 Graph-B 类型
 * 调用 get_road 函数获取最短路径，将逆序保存在数组 road 中
 */
struct SPFA {
    bool visited[MAXN];    //标记数组
    int dist[MAXN];        //源点到顶点i的最短距离
    int path[MAXN];        //记录最短路的路径
    int enqueue_num[MAXN]; //记录入队次数

    bool solve(int b, int e, int start, Graph &graph) {
        memset(visited, false, sizeof(visited));
        memset(enqueue_num, 0, sizeof(enqueue_num));
        for (int i = b; i < e; i++) {
            dist[i] = INT_MAX;
            path[i] = start;
        }
        queue<int> Q;
        Q.push(start);
        dist[start] = 0;
        visited[start] = true;
        enqueue_num[start]++;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            visited[u] = 0;
            for (int v = graph.head[u]; v != -1; v = graph.edge[v].next) {
                int to = graph.edge[v].to;
                if (dist[u] + graph.edge[v].cost < dist[to]) {
                    dist[to] = dist[u] + graph.edge[v].cost;
                    path[v] = u;
                    if (!visited[to]) {
                        Q.push(to);
                        enqueue_num[to]++;
                        if (enqueue_num[to] >= e)
                            return false;
                        visited[to] = 1;
                    }
                }
            }
        }
        return true;
    }

    int get_road(int n, int *road) {
        int cur_node = n;
        int cnt = 0;
        while (cur_node != -1) {
            road[cnt++] = cur_node;
            cur_node = path[cur_node];
        }
        return cnt;
    }
};