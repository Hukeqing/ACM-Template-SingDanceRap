#include <bits/stdc++.h>

#define N 200000
using namespace std;

typedef long long ll;

int n, m, r;
ll p;

struct Graph {
    struct Edge {
        int to, next;
    } eg[N * 2];

    int head[N];
    int val[N];
    int tot;

    void init(int n) {
        tot = 0;
        memset(head, -1, sizeof(int) * (n + 3));
        memset(val, 0, sizeof(int) * (n + 3));
    }

    void addEdge(int sta, int end) {
        eg[tot].to = end;
        eg[tot].next = head[sta];
        head[sta] = tot++;
    }
} gh;

struct SegTree {
    ll data[N << 2];
    ll lazy[N << 2];

    static inline int lson(int k) { return k << 1; }

    static inline int rson(int k) { return (k << 1) | 1; }

    static inline int fat(int l, int r) { return (l + r) >> 1; }

    inline void up(int k) {
        data[k] = (data[lson(k)] + data[rson(k)]) % p;
    }

    inline void set(int k, ll len, ll value) {
        data[k] += value * len % p;
        data[k] %= p;
        lazy[k] += value;
        lazy[k] %= p;
    }

    inline void push(int k, int l, int r) {
        if (lazy[k] == 0) return;
        if (l == r) return;
        set(lson(k), fat(l, r) - l + 1, lazy[k]);
        set(rson(k), r - fat(l, r), lazy[k]);
        lazy[k] = 0;
    }

    // 建树 [l, r]
    void build(int k, int l, int r, int *a) {
        lazy[k] = 0;
        if (l == r) {
            data[k] = a[l];
            return;
        }
        build(lson(k), l, fat(l, r), a);
        build(rson(k), fat(l, r) + 1, r, a);
        up(k);
    }

    // 区间更新
    void update(int k, int l, int r, int x, int y, int value) {
        if (l == x && r == y) {
            set(k, r - l + 1, value);
            return;
        }
        push(k, l, r);
        int mid = fat(l, r);
        if (y <= mid) {
            update(lson(k), l, mid, x, y, value);
        } else if (x > mid) {
            update(rson(k), mid + 1, r, x, y, value);
        } else {
            update(lson(k), l, mid, x, mid, value);
            update(rson(k), mid + 1, r, mid + 1, y, value);
        }
        up(k);
    }

    // 单点更新
    void update(int k, int l, int r, int x, int value) {
        if (l == r && l == x) {
            set(k, 1, value);
            return;
        }
        push(k, l, r);
        int mid = fat(l, r);
        if (x <= mid) {
            update(lson(k), l, mid, x, value);
        } else {
            update(rson(k), mid + 1, r, x, value);
        }
        up(k);
    }

    // 询问区间和
    ll query(int k, int l, int r, int x, int y) {
        if (l == x && r == y)
            return data[k];
        push(k, l, r);
        int mid = fat(l, r);
        if (y <= mid) {
            return query(lson(k), l, mid, x, y);
        } else if (x > mid) {
            return query(rson(k), mid + 1, r, x, y);
        } else {
            return (query(lson(k), l, mid, x, mid) + query(rson(k), mid + 1, r, mid + 1, y)) % p;
        }
    }
} sgt;

struct TreeChain {
    int top[N]; // 链顶端点
    int fa[N]; // 父亲节点
    int son[N]; // 重儿子
    int deep[N]; // 深度
    int num[N]; // 儿子节点数（包括自己）

    int id[N]; // 在线段树中的ID，
    int fp[N]; // 线段树中ID对应的点
    int tot;

    void dfs(int u, int pre, int d) {
        num[u] = 1;
        deep[u] = d;
        fa[u] = pre;
        son[u] = -1;
        for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
            int v = gh.eg[i].to;
            if (v == pre) continue;
            dfs(v, u, d + 1);
            num[u] += num[v];
            if (son[u] == -1 || num[v] > num[son[u]]) {
                son[u] = v;
            }
        }
    }

    void getpos(int u, int sp) {
        top[u] = sp;
        id[u] = tot++;
        fp[id[u]] = u;
        if (son[u] == -1) return;
        getpos(son[u], sp);
        for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
            int v = gh.eg[i].to;
            if (v == son[u] || v == fa[u]) continue;
            getpos(v, v);
        }
    }

    // start是线段树中的ID起始数值
    void build(int n, int root = 1, int start = 1) {
        tot = start;
        // deep起始值如果是0，则遇到数据错误超出这棵树，有可能死循环
        // dfs(root, 0, 0);
        dfs(root, 0, 1);
        getpos(root, root);
    }

    int lca(int u, int v) {
        int f1 = top[u];
        int f2 = top[v];
        while (f1 != f2) {
            if (deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            u = fa[f1];
            f1 = top[u];
        }
        return deep[u] < deep[v] ? u : v;
    }

    void update(int u, int v, int val) {
        int f1 = top[u];
        int f2 = top[v];
        while (f1 != f2) {
            if (deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            sgt.update(1, 1, n, id[f1], id[u], val);
            u = fa[f1];
            f1 = top[u];
        }
        if (id[u] > id[v]) swap(u, v);
        sgt.update(1, 1, n, id[u], id[v], val);
    }

    ll query(int u, int v) {
        ll ans = 0;
        int f1 = top[u];
        int f2 = top[v];
        while (f1 != f2) {
            if (deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            ans += sgt.query(1, 1, n, id[f1], id[u]);
            ans %= p;
            u = fa[f1];
            f1 = top[u];
        }
        if (id[u] > id[v]) swap(u, v);
        ans += sgt.query(1, 1, n, id[u], id[v]);
        ans %= p;
        return ans;
    }
} tch;

int a[N];

int main() {
#ifdef ACM_LOCAL
    freopen("../std.in", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> r >> p;
    gh.init(n);
    for (int i = 1; i <= n; i++) cin >> gh.val[i];
    int x, y;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        gh.addEdge(x, y);
        gh.addEdge(y, x);
    }
    tch.build(1, r);
    for (int i = 1; i <= n; i++) {
        a[tch.id[i]] = gh.val[i];
    }
    sgt.build(1, 1, n, a);
    int opt;
    int z;
    while (m--) {
        cin >> opt;
        switch (opt) {
            case 1:
                cin >> x >> y >> z;
                tch.update(x, y, z);
                break;
            case 2:
                cin >> x >> y;
                cout << tch.query(x, y) << endl;
                break;
            case 3:
                cin >> x >> y;
                sgt.update(1, 1, n, tch.id[x], tch.id[x] + tch.num[x] - 1, y);
                break;
            default:
                cin >> x;
                cout << sgt.query(1, 1, n, tch.id[x], tch.id[x] + tch.num[x] - 1) << endl;
        }
    }
    return 0;
}
