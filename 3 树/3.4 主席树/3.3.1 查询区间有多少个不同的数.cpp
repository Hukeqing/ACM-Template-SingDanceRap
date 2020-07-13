#include <bits/stdc++.h>

using namespace std;

/*
 * 给出一个序列，查询区间内有多少个不相同的数
 * 1、先把数组保存在 a 数组中
 * 2、调用 build 函数
 * 3、使用 query 函数询问
 */

const int MAXN = 30010;
const int M = MAXN * 100;
int n, q, tot;
int a[MAXN];
int T[MAXN], lson[M], rson[M], c[M];

int __build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if (l != r) {
        int mid = (l + r) >> 1;
        lson[root] = __build(l, mid);
        rson[root] = __build(mid + 1, r);
    }
    return root;
}

int update(int root, int pos, int val) {
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int query(int root, int pos) {
    int ret = 0;
    int l = 1, r = n;
    while (pos < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            r = mid;
            root = lson[root];
        } else {
            ret += c[lson[root]];
            root = rson[root];
            l = mid + 1;
        }
    }
    return ret + c[root];
}

void build() {
    T[n + 1] = __build(1, n);
    map<int, int> mp;
    for (int i = n; i >= 1; i--) {
        if (mp.find(a[i]) == mp.end()) {
            //没找到重复的点，直接更新
            T[i] = update(T[i + 1], i, 1);
        } else {
            //先在新树上去掉先前重复的点
            int tmp = update(T[i + 1], mp[a[i]], -1);
            //在当前位置添加这个点，保持每棵树上不存在重复节点
            T[i] = update(tmp, i, 1);
        }
        mp[a[i]] = i;
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    build();

    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(T[l], r) << endl;
    }

    return 0;
}