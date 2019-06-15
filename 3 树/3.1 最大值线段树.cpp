/*
 最大值线段树
 先使用 build(1, l, r) 函数来建树
 然后使用单点修改的方式来完成建树
 */
const int MAXN = 10010;

struct node {
    int l, r;
    int Max;
}segTree[MAXN * 3];
void build(int i, int l, int r) {
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].Max = 0;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(i << 1, l, mid);
    build((i << 1) | 1, mid + 1, r);
}
void push_up(int i) {
    segTree[i].Max = max(segTree[i << 1].Max, segTree[(i << 1) | 1].Max);
}
// 更新线段树的第 k 个值为 val
void update(int i, int k, int val) {
    if(segTree[i].l == k && segTree[i].r == k) {
        segTree[i].Max = val;
        return;
    }
    int mid = (segTree[i].l + segTree[i].r) / 2;
    if(k <= mid)update(i << 1, k, val);
    else update((i << 1) | 1, k, val);
    push_up(i);
}
//查询线段树中 [l,r] 的最大值
int query(int i, int l, int r) {
    if(segTree[i].l == l && segTree[i].r == r)
        return segTree[i].Max;
    int mid = (segTree[i].l + segTree[i].r) / 2;
    if (r <= mid) return query(i << 1, l, r);
    else if (l > mid) return query((i << 1) | 1, l, r);
    else return max(query(i << 1, l, mid), query((i << 1) | 1, mid + 1, r));
}
