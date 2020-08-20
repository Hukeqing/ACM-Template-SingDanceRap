#define MAXN 500100
#define LOG 30

struct LCA {
    int fa[MAXN][LOG], depth[MAXN];
    vector<int> link[MAXN];

    void init(int root) {
        depth[root] = 0;
    }

    /**
     * 加边
     * @param u
     * @param v
     */
    void addEdge(int u, int v) {
        link[u].push_back(v);
        link[v].push_back(u);
    }

    /**
     * dfs 建树
     * @param cur 根
     * @param pre
     */
    void dfs(int cur, int pre = 0) {
        memset(fa[cur], 0, sizeof(fa[cur]));
        fa[cur][0] = pre;
        int p = 0;
        while (fa[cur][p++])
            fa[cur][p] = fa[fa[cur][p - 1]][p - 1];
        for (auto item : link[cur]) {
            if (item != pre) {
                depth[item] = depth[cur] + 1;
                dfs(item, cur);
            }
        }
    }

    int kfa(int cur, int k) {
        int bit = 0;
        while (k) {
            if (k & 1) cur = fa[cur][bit];
            k >>= 1;
            bit++;
        }
        return cur;
    }

    int lca(int u, int v) {
        int minDepth = min(depth[u], depth[v]);
        u = kfa(u, depth[u] - minDepth);
        v = kfa(v, depth[v] - minDepth);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
} lca;
