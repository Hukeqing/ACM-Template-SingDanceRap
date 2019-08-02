#include <bits/stdc++.h>

using namespace std;

#ifdef ACM_LOCAL
const int maxn = 100;
#endif
#ifndef ACM_LOCAL
const int maxn = 100010;
#endif
//a-原数组；b-树下数组；tot-树上节点数，用于建树；root-根节点下标数组
int a[maxn], b[maxn], tot, root[maxn];
int size;//压缩相同数字后的数量
map<int, int> mat;//每个数字对应的b中数组的位置

struct Tree {
    //lc-左子树根节点；rc-右子树根节点；sum-节点权值
    int lc, rc, sum;
} tree[maxn * 20];

//建立左边界为l，右边界为r的区间子树，返回根节点的下标
int build(int l, int r) {
    int o = tot++;
    tree[o].sum = 0;
    if (l == r)
        return o;
    int mid = (l + r) / 2;
    tree[o].lc = build(l, mid);
    tree[o].rc = build(mid + 1, r);
    return o;
}

//将第i位，处于l-r区间内的值添加v；在原来before树的基础上，新建一棵树并返回根节点的下标
int update(int i, int l, int r, int before, int v) {
    int o = tot++;
    tree[o] = tree[before];
    tree[o].sum += v;
    if (l == r)
        return o;
    //更新左子树（或右子树）
    int mid = (l + r) / 2;
    if (i <= mid)
        tree[o].lc = update(i, l, mid, tree[before].lc, v);
    else
        tree[o].rc = update(i, mid + 1, r, tree[before].rc, v);
    return o;
}

//查询i树到j树（i比j晚）之间，在区间l和r中满足在x位置之前的数有多少个
int query(int i, int j, int x, int l, int r) {
    if (l == r)
        return tree[i].sum - tree[j].sum;
    int mid = (l + r) / 2;
    int res = 0;
    if (x <= mid)
        res += query(tree[i].lc, tree[j].lc, x, l, mid);
    else {
        res += tree[tree[i].lc].sum - tree[tree[j].lc].sum;
        res += query(tree[i].rc, tree[j].rc, x, mid + 1, r);
    }
    return res;
}

//询问l和r之间在x位置之前的数的个数
int queryRes(int l, int r, int x) {
    return query(root[r], root[l - 1], x, 1, size);
}

int main() {
#ifdef ACM_LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int t;
    scanf("%d", &t);
    int cnt = 1;
    while (t--) {
        /**************样例输入****************/
        printf("Case %d:\n", cnt++);
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        /**************输入完毕****************/

        /****************建树******************/
        sort(b + 1, b + n + 1);

        size = unique(b + 1, b + n + 1) - b - 1;//压缩后的大小

        //记录每个数排序之后在第几位
        for (int i = 1; i <= size; i++)
            mat[b[i]] = i;

        tot = 0;
        root[0] = build(1, size);//初始化建0树

        //记录数字出现的个数，因此更新为1
        for (int i = 1; i <= n; i++)
            root[i] = update(mat[a[i]], 1, size, root[i - 1], 1);
        /****************完毕******************/

        while (m--) {
            int l, r, h;
            scanf("%d%d%d", &l, &r, &h);
            l++, r++;
            int k = upper_bound(b + 1, b + size + 1, h) - b - 1;
            if (k)
                printf("%d\n", queryRes(l, r, k));
            else
                printf("0\n");
        }
    }
    return 0;
}