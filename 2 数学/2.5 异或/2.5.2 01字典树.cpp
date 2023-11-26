#include<bits/stdc++.h>

#define NUM 2000
using namespace std;
#define ll long long

int n;
int a[NUM];

/**
 * 01字典树
 */
struct Trie01 {
    /**
     * 最大位数，视情况而定，一般int以内使用31即可
     */
    static const int bitSize = 31;
    /**
     * 数组实际大小=数据量大小*最大位数
     */
    static const int N = NUM * bitSize;
    int son[N][2]{};
    int cnt[N]{};
    int tot{};

    /**
     * 初始化节点上的计数器、每个节点的子节点指针、用于开点的tot
     */
    void init() {
        memset(cnt, 0, sizeof(int) * N);
        memset(son, 0, sizeof(int) * (N * 2));
        tot = 2;
    }

    /**
     * 增加指定字符的出现次数
     * @param x 指定字符
     * @param v 出现次数
     */
    void add(int x, int v) {
        int root = 1;
        for (int j = bitSize; j >= 0; j--) {
            int bit = (x >> j) & 1;
            if (!son[root][bit]) {
                son[root][bit] = tot++;
            }
            cnt[son[root][bit]] += v;
            root = son[root][bit];
        }
    }

    /**
     * 求出指定数字的最大匹配异或
     * @param x 指定数字
     * @return 最大匹配异或值
     */
    int maXOR(int x) {
        int res = 0;
        int root = 1;
        for (int k = bitSize; k >= 0; k--) {
            int bit = (x >> k) & 1;
            if (cnt[son[root][!bit]]) {
                res += (1 << k);
                root = son[root][!bit];
            } else {
                root = son[root][bit];
            }
        }
        return res;
    }

} trie01;

int main() {
#ifdef ACM_LOCAL
    freopen("../std.in", "r", stdin);
#endif
    int t;
    cin >> t;
    while (t--) {
        trie01.init();
        cin >> n;
        int x;
        for (int i = 0; i < n; i++) {
            cin >> x;
            a[i] = x;
            trie01.add(x, 1);
        }
        int ans = -1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                trie01.add(a[i], -1);
                trie01.add(a[j], -1);
                /****/
                ans = max(ans, trie01.maXOR(a[i] + a[j]));
                /****/
                trie01.add(a[i], 1);
                trie01.add(a[j], 1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
