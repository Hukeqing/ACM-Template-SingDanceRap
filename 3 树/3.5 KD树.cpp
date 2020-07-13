/*
 * k-d Tree 多维二叉树树，离线查询离某个值最近的前 m 个值
 * 顺序维度分类，默认从第一维开始，对随机数的查找速度友好，对特定数据查找非常慢
 * 1、将数据读入至 a 数组
 * 2、kd.build(0, n - 1) 一下
 * 3、kd.query(ask, m) 询问答案，存放在 nq 中，默认按照
 */
#define sqr(x) ((x)*(x))
const int N = 55555, K = 5;

int k, n, idx;   // k为维数,n为点数
struct point {
    int x[K]{};

    point() = default;

    bool operator<(const point &u) const {
        return x[idx] < u.x[idx];
    }
} a[N];

typedef pair<double, point> tp;

priority_queue<tp, vector<tp>, greater<tp> > nq;

struct kdTree {
    point pt[N * 4];
    int son[N * 4]{};

    void build(int l, int r, int rt = 1, int dep = 0) {
        if (l > r) return;
        son[rt] = r - l;
        son[rt * 2] = son[rt * 2 + 1] = -1;
        idx = dep % k;
        int mid = (l + r) / 2;
        nth_element(a + l, a + mid, a + r + 1);
        pt[rt] = a[mid];
        build(l, mid - 1, rt * 2, dep + 1);
        build(mid + 1, r, rt * 2 + 1, dep + 1);
    }

    void query(point p, int m, int rt = 1, int dep = 0) {
        if (son[rt] == -1) return;
        tp nd(0, pt[rt]);
        for (int i = 0; i < k; i++) nd.first += sqr(nd.second.x[i] - p.x[i]);
        int dim = dep % k, x = rt * 2, y = rt * 2 + 1, fg = 0;
        if (p.x[dim] >= pt[rt].x[dim]) swap(x, y);
        if (son[x] != -1) query(p, m, x, dep + 1);
        if (nq.size() < m) nq.push(nd), fg = 1;
        else {
            if (nd.first < nq.top().first) nq.pop(), nq.push(nd);
            if (sqr(p.x[dim] - pt[rt].x[dim]) < nq.top().first) fg = 1;
        }
        if (son[y] != -1 && fg) query(p, m, y, dep + 1);
    }
} kd;