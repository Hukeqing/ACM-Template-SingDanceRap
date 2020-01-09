const int MAXN = 100000 + 10;

struct Node {
    int next;
    int cnt;
} fa[MAXN];

int finds(int x) {
    return x == fa[x].next ? x : finds(fa[x].next);
}

void unions(int a, int b) {
    int r1 = finds(fa[a].next);
    int r2 = finds(fa[b].next);
    if (r1 != r2) {
        fa[r1].next = r2;
        fa[r2].cnt += fa[r1].cnt;
    }
}

void init(int b, int e) {
    for (int i = b; i < e; i++) {
        fa[i].next = i;
        fa[i].cnt = 1;
    }
}

int count(int k) {
    return fa[finds(fa[k].next)].cnt;
}