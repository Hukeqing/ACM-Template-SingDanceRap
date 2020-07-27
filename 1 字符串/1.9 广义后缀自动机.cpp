/**
 *  扩展后缀自动机——后缀自动机在字典树上的扩展
 *  性质同普通自动机
 *  同时可以对多个串处理
 */


#define MAXN 2000000            // 双倍字符串长度
#define CHAR_NUM 30             // 字符集个数，注意修改下方的 (-'a')
#define NUM 15                  // 字符串个数

struct exSAM {
    int len[MAXN];              // 节点长度
    int link[MAXN];             // 后缀链接，link
    int next[MAXN][CHAR_NUM];   // 转移
    int tot;                    // 节点总数：[0, tot)
    /**
     * 可选变量区
     */
    int lenSorted[MAXN];        // 按照 len 排序后的数组，仅排序 [1, tot) 部分，最终下标范围 [0, tot - 1)
    int sizeC[MAXN][NUM];       // 位运算表示某个字符串是否能够到达这个节点
    int curString;              // 字符串实际个数
    /**
     * 基数排序使用的辅助空间数组
     */
    int lc[MAXN];               // 统计个数

    void init() {
        tot = 1;
        link[0] = -1;
    }

    int insertSAM(int last, int c) {
        int cur = next[last][c];
        len[cur] = len[last] + 1;
        int p = link[last];
        while (p != -1) {
            if (!next[p][c]) next[p][c] = cur;
            else break;
            p = link[p];
        }
        if (p == -1) {
            link[cur] = 0;
            return cur;
        }
        int q = next[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            return cur;
        }
        int clone = tot++;
        for (int i = 0; i < CHAR_NUM; ++i)
            next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
        len[clone] = len[p] + 1;
        while (p != -1 && next[p][c] == q) {
            next[p][c] = clone;
            p = link[p];
        }
        link[clone] = link[q];
        link[cur] = clone;
        link[q] = clone;

        return cur;
    }

    int insertTrie(int cur, int c) {
        if (!next[cur][c]) next[cur][c] = tot++;
        sizeC[next[cur][c]][curString]++;
        return next[cur][c];
    }

    void insert(const string &s) {
        int root = 0;
        for (auto ch : s) root = insertTrie(root, ch - 'a');
        curString++;
    }

    void insert(const char *s, int n) {
        int root = 0;
        for (int i = 0; i < n; ++i) root = insertTrie(root, s[i] - 'a');
        curString++;
    }

    void build() {
        queue<pair<int, int>> q;
        for (int i = 0; i < 26; ++i)
            if (next[0][i]) q.push({i, 0});
        while (!q.empty()) {
            auto item = q.front();
            q.pop();
            auto last = insertSAM(item.second, item.first);
            for (int i = 0; i < 26; ++i)
                if (next[last][i]) q.push({i, last});
        }
    }

    /* 工具函数 */

    /**
     * 计算 lenSorted 数组
     */
    void sortLen() {
        for (int i = 1; i < tot; ++i) lc[i] = 0;
        for (int i = 1; i < tot; ++i) lc[len[i]]++;
        for (int i = 2; i < tot; ++i) lc[i] += lc[i - 1];
        for (int i = 1; i < tot; ++i) lenSorted[--lc[len[i]]] = i;
    }

    /**
     * 计算 sizeC 数组（使用基数排序解决）
     * ！！！请先调用 sortLen ！！！
     * 效率略低但是同时可以计算出 lenSorted 数组
     */
    void getSizeLen() {
        for (int i = tot - 2; i >= 0; --i)
            for (int j = 0; j < curString; ++j)
                sizeC[link[lenSorted[i]]][j] += sizeC[lenSorted[i]][j];
    }

    void debug() {
        cout << "     i      len      link       ";
        for (int i = 0; i < 26; ++i)
            cout << "  " << (char) ('a' + i);
        cout << endl;
        for (int i = 0; i < tot; ++i) {
            cout << "i: " << setw(3) << i
                 << " len: " << setw(3) << len[i]
                 << " link: " << setw(3) << link[i]
                 << " Next: ";
            for (int j = 0; j < CHAR_NUM; ++j) {
                cout << setw(3) << next[i][j];
            }
            cout << endl;
        }
    }
} exSam;
