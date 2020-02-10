/*
 * 需要一维 hash
 */

// 30 > MAXN * log(MAXN)
struct ChaTree {
    int value[MAXN * 30];
    int lson[MAXN * 30];
    int rson[MAXN * 30];
    int root[MAXN];
    int tot;

    // 建树 [1, n]
    void build(int *a, int n, HashData &hashData) {
        tot = 1;
        root[0] = 0;
        for (int i = 1; i <= n; ++i)
            update(1, n, root[i - 1], root[i], hashData.my_hash(a[i]));
    }

    void update(int l, int r, int pre, int &nex, int pos) {
        value[tot] = value[pre] + 1;
        lson[tot] = lson[pre];
        rson[tot] = rson[pre];
        nex = tot++;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (mid >= pos) update(l, mid, lson[pre], lson[nex], pos);
        else update(mid + 1, r, rson[pre], rson[nex], pos);
    }

    // 询问, l = 1, r = n, x = chaTree.root[x - 1], y = chaTree.root[y], k 为第 k 小, 需要反 hash
    int query(int l, int r, int x, int y, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        int sum = value[lson[y]] - value[lson[x]];
        if (sum >= k) return query(l, mid, lson[x], lson[y], k);
        else return query(mid + 1, r, rson[x], rson[y], k - sum);
    }
};
