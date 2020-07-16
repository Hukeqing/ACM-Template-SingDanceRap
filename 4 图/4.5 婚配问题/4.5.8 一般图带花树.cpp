const int maxn = 505;
const int maxm = maxn * maxn * 2;
int n, m, que[maxm], ql, qr, pre[maxn], tim = 0;
struct edge {
    int v, nxt;
} e[maxm];
int h[maxn], tot = 0;
int match[maxn], f[maxn], tp[maxn], tic[maxn];

int find(int x) {
    return f[x] == x ? f[x] : f[x] = find(f[x]);
}

void add(int u, int v) {
    e[++tot] = (edge) {v, h[u]};
    h[u] = tot;
}

int lca(int x, int y) {
    for (++tim;; swap(x, y))
        if (x) {
            x = find(x);
            if (tic[x] == tim) return x; else tic[x] = tim, x = pre[match[x]];
        }
}

void shrink(int x, int y, int p) {
    while (find(x) != p) {
        pre[x] = y, y = match[x];
        if (tp[y] == 2) tp[y] = 1, que[++qr] = y;
        if (find(x) == x) f[x] = p;
        if (find(y) == y) f[y] = p;
        x = pre[y];
    }
}

bool aug(int s) {
    for (int i = 1; i <= n; ++i) f[i] = i;
    memset(tp, 0, sizeof tp), memset(pre, 0, sizeof pre);
    tp[que[ql = qr = 1] = s] = 1; // 1: type A ; 2: type B
    while (ql <= qr) {
        int x = que[ql++];
        for (int i = h[x], v = e[i].v; i; i = e[i].nxt, v = e[i].v) {
            if (find(v) == find(x) || tp[v] == 2) continue;
            if (!tp[v]) {
                tp[v] = 2, pre[v] = x;
                if (!match[v]) {
                    for (int now = v, last, tmp; now; now = last) {
                        last = match[tmp = pre[now]];
                        match[now] = tmp, match[tmp] = now;
                    }
                    return true;
                }
                tp[match[v]] = 1, que[++qr] = match[v];
            } else if (tp[v] == 1) {
                int l = lca(x, v);
                shrink(x, v, l);
                shrink(v, x, l);
            }
        }
    }
    return false;
}

int solved() {
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans += (!match[i] && aug(i));
    return ans;
}
