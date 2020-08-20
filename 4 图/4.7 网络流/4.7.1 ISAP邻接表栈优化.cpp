const int MAXN = "Edit";

namespace flow {
    struct edge {
        int to, cap, flow, rev;
    };
    vector<edge> g[MAXN];
    int s, t, nCnt, d[MAXN], cur[MAXN];
    queue<int> q;

    void init(int ss, int tt, int nn) {
        s = ss;
        t = tt;
        for (int i = 1; i <= nCnt; ++i) g[i].clear();
        nCnt = nn;
    }

    void addEdge(int l, int r, int w) {
        g[l].push_back((edge) {r, w, 0, (int) g[r].size()});
        g[r].push_back((edge) {l, 0, 0, (int) g[l].size() - 1});
    }

    bool bfs() {
        for (int i = 1; i <= nCnt; ++i)
            d[i] = i == s ? 0 : -1;
        q.push(s);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int i = 0; i < (int) g[p].size(); ++i) {
                edge e = g[p][i];
                if (e.cap > e.flow && d[e.to] == -1) {
                    d[e.to] = d[p] + 1;
                    q.push(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    int dfs(int p, int a) {
        if (p == t) return a;
        int ans = 0, now;
        for (int &i = cur[p]; i < (int) g[p].size(); ++i) {
            edge &e = g[p][i];
            if (e.cap > e.flow && d[p] + 1 == d[e.to]) {
                now = dfs(e.to, min(a, e.cap - e.flow));
                e.flow += now;
                g[e.to][e.rev].flow -= now;
                ans += now;
                a -= now;
                if (!a) break;
            }
        }
        return ans;
    }

    int solve() {
        int ans = 0;
        while (bfs()) {
            for (int i = 1; i <= nCnt; ++i) cur[i] = 0;
            ans += dfs(s, 1e9);
        }
        return ans;
    }
}
