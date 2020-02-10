struct SegTree {
    ll s[N << 1], laz[N << 1];
    bool vis[N << 1];

    inline int static get(int l, int r) {
        return (l + r) | (l != r);
    }

    inline void up(int l, int r) {
        int mid = (l + r) >> 1;
        s[get(l, r)] = s[get(l, mid)] + s[get(mid + 1, r)];
    }

    void build(int l, int r) {
        assert(vis[get(l, r)] == false);
        vis[get(l, r)] = true;
        laz[get(l, r)] = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid);
        build(mid + 1, r);
        up(l, r);
    }

    inline void push(int l, int r) {
        int k = get(l, r);
        if (laz[k]) {
            int mid = (l + r) >> 1;
            s[get(l, mid)] += laz[k] * (mid - l + 1);
            s[get(mid + 1, r)] += laz[k] * (r - mid);
            laz[get(l, mid)] += laz[k];
            laz[get(mid + 1, r)] += laz[k];
            laz[k] = 0;
        }
    }

    void update(int l, int r, int x, int y, ll w) {
        if (l == x && y == r) {
            s[get(l, r)] += w * (r - l + 1);
            laz[get(l, r)] += w;
            return;
        }
        push(l, r);
        int mid = (l + r) >> 1;
        if (y <= mid) {
            update(l, mid, x, y, w);
        } else if (x > mid) {
            update(mid + 1, r, x, y, w);
        } else {
            update(l, mid, x, mid, w);
            update(mid + 1, r, mid + 1, y, w);
        }
        up(l, r);
    }

    ll query(int l, int r, int x, int y) {
        if (l == x && y == r) {
            return s[get(l, r)];
        }
        push(l, r);
        int mid = (l + r) >> 1;
        if (y <= mid) {
            return query(l, mid, x, y);
        } else if (x > mid) {
            return query(mid + 1, r, x, y);
        } else {
            return query(l, mid, x, mid) + query(mid + 1, r, mid + 1, y);
        }
    }
};
