struct ISAP {
    int Q[MAXN];
    int S[MAXN];
    int gap[MAXN], dep[MAXN], cur[MAXN];

    void BFS(int start, int end, Graph &graph) {
        memset(dep, -1, sizeof(dep));
        memset(gap, 0, sizeof(gap));
        gap[0] = 1;
        int front = 0, rear = 0;
        dep[end] = 0;
        Q[rear++] = end;
        while (front != rear) {
            int u = Q[front++];
            for (int i = graph.head[u]; i != -1; i = graph.edge[i].next) {
                int v = graph.edge[i].to;
                if (dep[v] != -1)
                    continue;
                Q[rear++] = v;
                dep[v] = dep[u] + 1;
                gap[dep[v]]++;
            }
        }
    }

    int solve(int start, int end, int N, Graph &graph) {
        BFS(start, end, graph);
        memcpy(cur, graph.head, sizeof(graph.head));
        int top = 0;
        int u = start;
        int ans = 0;
        while (dep[start] < N) {
            if (u == end) {
                int Min = INT_MAX;
                int inser = 0;
                for (int i = 0; i < top; i++) {
                    if (Min > graph.edge[S[i]].cap - graph.edge[S[i]].flow) {
                        Min = graph.edge[S[i]].cap - graph.edge[S[i]].flow;
                        inser = i;
                    }
                }
                for (int i = 0; i < top; i++) {
                    graph.edge[S[i]].flow += Min;
                    graph.edge[S[i] ^ 1].flow -= Min;
                }
                ans += Min;
                top = inser;
                u = graph.edge[S[top] ^ 1].to;
                continue;
            }
            bool flag = false;
            int v = 0;
            for (int i = cur[u]; i != -1; i = graph.edge[i].next) {
                v = graph.edge[i].to;
                if (graph.edge[i].cap - graph.edge[i].flow && dep[v] + 1 == dep[u]) {
                    flag = true;
                    cur[u] = i;
                    break;
                }
            }
            if (flag) {
                S[top++] = cur[u];
                u = v;
                continue;
            }
            int Min = N;
            for (int i = graph.head[u]; i != -1; i = graph.edge[i].next)
                if (graph.edge[i].cap - graph.edge[i].flow && dep[graph.edge[i].to] < Min) {
                    Min = dep[graph.edge[i].to];
                    cur[u] = i;
                }
            gap[dep[u]]--;
            if (!gap[dep[u]])
                return ans;
            dep[u] = Min + 1;
            gap[dep[u]]++;
            if (u != start)
                u = graph.edge[S[--top] ^ 1].to;
        }
        return ans;
    }
};
