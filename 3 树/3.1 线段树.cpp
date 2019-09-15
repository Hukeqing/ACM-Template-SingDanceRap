struct SegTree {
    int data[MAXN << 2];
    int lazy[MAXN << 2];

    static inline int lson(int k) { return k << 1; }

    static inline int rson(int k) { return (k << 1) | 1; }

    static inline int fat(int l, int r) { return (l + r) >> 1; }

    inline void up(int k) {
        data[k] = data[lson(k)] + data[rson(k)];
    }

    inline void set(int k, int len, int value) {
        data[k] += value * len;
        lazy[k] += value;
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
    int query(int k, int l, int r, int x, int y) {
        if (l == x && r == y)
            return data[k];
        push(k, l, r);
        int mid = fat(l, r);
        if (y <= mid) {
            return query(lson(k), l, mid, x, y);
        } else if (x > mid) {
            return query(rson(k), mid + 1, r, x, y);
        } else {
            return query(lson(k), l, mid, x, mid) + query(rson(k), mid + 1, r, mid + 1, y);
        }
    }
};