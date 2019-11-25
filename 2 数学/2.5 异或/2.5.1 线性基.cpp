//所谓线性基，就是线性代数里面的概念。一组线性无关的向量便可以作为一组基底，张起一个线性的向量空间，这个基地又称之为线性基。这个线性基的基底进行线性运算，可以表示向量空间内的所有向量，也即所有向量可以拆成基底的线性组合。
//这篇用了前缀和能快速计算多次询问中的不同区间的最大异或和
const int maxn = (int) 5e5 + 100;
int p[maxn][31], pos[maxn][31];
int n, q;
int lastans = 0;

typedef long long ll;

void push_back(int x, int i) {
    for (int j = 0; j <= 30; j++) {
        p[i][j] = p[i - 1][j];
        pos[i][j] = pos[i - 1][j];
    }
    int ti = i;
    for (int j = 30; j >= 0; j--) {
        if (x & (1 << j)) {
            if (!p[i][j]) {
                p[i][j] = x;
                pos[i][j] = ti;
                break;
            }
            if (pos[i][j] < ti) {
                swap(p[i][j], x);
                swap(pos[i][j], ti);
            }
            x ^= p[i][j];
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        lastans = 0;
//        memset(p, 0, sizeof(p));
//        memset(pos, 0, sizeof(pos));
        cin >> n >> q;
        int x;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            push_back(x, i);
        }
        while (q--) {
            int e, l, r;
            cin >> e;
            if (e == 1) {
                cin >> l;
                l ^= lastans;
                push_back(l, n + 1);
                n++;
            } else {
                cin >> l >> r;
                l = (l ^ lastans) % n + 1;
                r = (r ^ lastans) % n + 1;
                if (l > r) {
                    swap(l, r);
                }
                int ret = 0;
                for (int i = 30; i >= 0; i--) {
                    if (pos[r][i] >= l && (ret ^ p[r][i]) > ret) {
                        ret ^= p[r][i];
                    }
                }
                cout << ret << endl;
                lastans = ret;
            }
        }
    }
}