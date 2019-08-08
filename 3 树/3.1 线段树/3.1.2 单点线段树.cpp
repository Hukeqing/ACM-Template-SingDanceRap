/*
 * 单点线段树，所有节点保存的值为某个叶子节点的值，如最大值线段树，而不是区间的值，如区间和
 * 所有方法中，只需要调用含有 inline 的函数，其他的函数为其内部实现
 * 先建树， build 参数为 a-原数组，l-原数组下标左界，r-原数组下标右界，范围 [l, r]。建空树可以不用参数 a
 * 单点更新与区间更新函数均为 update，只有参数个数不同
 * 询问答案时默认直接返回值，可以修改 query 函数来改成返回此值对应的最小区间
 * 
 * 当前确定无误的操作：建空树、单点修改、区间查询
 */

#define MAXN 200100 // 线段树的叶子节点个数
struct SegTree
{
    struct TreeNode
    {
        int value;
        int lazy;
        TreeNode() : lazy(0), value(0) {}
        inline int getvalue(int othervalue = 0)
        {
            return value + lazy + othervalue;
        }
    };
    TreeNode node[MAXN * 3];
    // 原数组的下标范围
    int al, ar;
    inline bool cmp(TreeNode &a, TreeNode &b)
    {
        return a.getvalue() > b.getvalue();
    }
    inline int cmp(int a, int b)
    {
        return cmp(node[a], node[b]) ? a : b;
    }
    inline int mid(int l, int r)
    {
        return (l + r) / 2;
    }
    // 求算当前节点的值
    inline void pull(int curnode)
    {
        node[curnode].value = node[cmp(curnode << 1, (curnode << 1) | 1)].getvalue();
    }
    // 建树。
    void build(int *a, int curl, int curr, int curnode)
    {
        if (curl == curr)
            node[curnode].value = a[curl];
        else
        {
            build(a, curl, mid(curl, curr), curnode << 1);
            build(a, mid(curl, curr) + 1, curr, (curnode << 1) | 1);
            pull(curnode);
        }
    }
    // push向下推lazy，仅推到需要的区间就停止。
    void push(int nl, int nr, int curl, int curr, int curnode, int lazyval)
    {
        if (curl == curr)
        {
            node[curnode].value = node[curnode].getvalue(lazyval);
            return;
        }
        else if ((nl <= curl && curr <= nr) || nr < curl || nl > curr) // 当前区间在所需要的区间内或者与所需要的区间无关时
        {
            node[curnode].lazy += lazyval;
            return;
        }
        else
        {
            lazyval += node[curnode].lazy;
            node[curnode].lazy = 0;
            if (lazyval == 0)
                return;
            push(nl, nr, curl, mid(curl, curr), curnode << 1, lazyval);
            push(nl, nr, mid(curl, curr) + 1, curr, (curnode << 1) | 1, lazyval);
            pull(curnode);
        }
    }
    // 单点更新
    void update(int k, int val, int curl, int curr, int curnode)
    {
        if (curl == curr)
        {
            node[curnode].value = val;
            return;
        }
        if (node[curnode].lazy)
            push(k, k, curl, curr, curnode, node[curnode].lazy);
        else if (k <= mid(curl, curr))
            update(k, val, curl, mid(curl, curr), curnode << 1);
        else
            update(k, val, mid(curl, curr) + 1, curr, (curnode << 1) | 1);
        pull(curnode);
    }
    // 区间更新
    void update(int ul, int ur, int val, int curl, int curr, int curnode)
    {
        if (ul <= curl && curr <= ur)
        {
            node[curnode].lazy = val;
            return;
        }
        if (ur < curl || ul > curr)
            return;
        if (node[curnode].lazy)
        {
            node[curnode].lazy = 0;
            push(ul, ur, curl, curr, curnode, node[curnode].lazy);
        }
        update(ul, ur, val, curl, mid(curl, curr), curnode << 1);
        update(ul, ur, val, mid(curl, curr) + 1, curr, (curnode << 1) | 1);
        pull(curnode);
    }
    // 区间查询
    int query(int ql, int qr, int curl, int curr, int curnode)
    {
        if (ql <= curl && curr <= qr) // 当前区间在询问区间内
            // return join(node[curnode].value, node[curnode].lazy);
            return curnode;
        if (node[curnode].lazy)
        {
            node[curnode].lazy = 0;
            push(ql, qr, curl, curr, curnode, node[curnode].lazy);
        }
        if (ql <= mid(curl, curr) && qr > mid(curl, curr))
        {
            return cmp(query(ql, qr, curl, mid(curl, curr), curnode << 1), query(ql, qr, mid(curl, curr) + 1, curr, (curnode << 1) | 1));
        }
        if (ql > mid(curl, curr))
        {
            return query(ql, qr, mid(curl, curr) + 1, curr, (curnode << 1) | 1);
        }
        else if (qr <= mid(curl, curr))
        {
            return query(ql, qr, curl, mid(curl, curr), curnode << 1);
        }
    }
    // 建树，数组和下标区间
    inline void build(int *a, int l, int r)
    {
        al = l;
        ar = r;
        build(a, l, r, 1);
    }
    inline void build(int l, int r)
    {
        al = l;
        ar = r;
    }
    // 单点更新，使下标为 k 的值变成 val
    inline void update(int k, int val)
    {
        update(k, val, al, ar, 1);
    }
    // 区间更新，使区间 [l, r] 的所有值增加 val
    inline void update(int l, int r, int val)
    {
        update(l, r, val, al, ar, 1);
    }
    // 询问答案
    inline int query(int l, int r)
    {
        return node[query(l, r, al, ar, 1)].getvalue();
    }
};