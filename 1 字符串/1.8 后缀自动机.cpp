/**
 *  后缀自动机
 *  求到达某个节点的所有等价类中最长字串：len[i]
 *  求到达某个节点的所有等价类中最短字串：len[link[i]] + 1
 *  求到达某个节点的子串个数：len[i] - len[link[i]]
 *  求到达某个节点的所有子串：len[i] * (len[i] + 1) / 2
 *  地上的节点(非clone节点) => sizeC = 1 的节点
 *  最小循环移位：双倍字符串然后求 SAM
 */

#define MAXN 2000000            // 双倍字符串长度
#define CHAR_NUM 30             // 字符集个数，注意修改下方的 (-'a')

struct SAM {
    int len[MAXN];              // 节点长度
    int link[MAXN];             // 后缀链接，link
    int next[MAXN][CHAR_NUM];   // 转移
    int last;                   // 最后状态
    int tot;                    // 节点总数：[0, tot)
    /**
     * 可选变量区
     */
    int lenSorted[MAXN];        // 按照 len 排序后的数组，仅排序 [1, tot) 部分，最终下标范围 [0, tot - 1)
    int linkD[MAXN];            // parent 树的度，用于拓扑
    int sizeC[MAXN];            // 节点 i 为结束结点的相同子串个数（所有不相同子串的数量相同）
    int count[MAXN];            // 以节点 i 为起点，沿着 next 指针能得到多少个不同的子串
    int firstPos[MAXN];         // 对于某个节点形成的子串，最早结束于字符串中第几个字符

    /**
     * 基数排序使用的辅助空间数组
     */
    int lc[MAXN];               // 统计个数

    /* build 函数*/

    void init() {
        tot = 1;
        link[0] = -1;
    }

    void reset() {
        last = 0;
        memset(next, 0, sizeof(next));
        memset(sizeC, 0, sizeof(sizeC));
    }

    void build(char c) {
        int cur = tot++;
        sizeC[cur] = 1;
        len[cur] = len[last] + 1;
        firstPos[cur] = len[last];
        int p = last;
        while (p != -1) {
            if (!next[p][c - 'a']) next[p][c - 'a'] = cur;
            else break;
            p = link[p];
        }
        if (p == -1) {
            link[cur] = 0;
            last = cur;
            return;
        }
        int q = next[p][c - 'a'];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            last = cur;
            return;
        }
        int clone = tot++;
        for (int i = 0; i < CHAR_NUM; ++i)
            next[clone][i] = next[q][i];
        len[clone] = len[p] + 1;
        firstPos[clone] = len[q];
        while (p != -1 && next[p][c - 'a'] == q) {
            next[p][c - 'a'] = clone;
            p = link[p];
        }
        link[clone] = link[q];
        link[cur] = clone;
        link[q] = clone;

        last = cur;
    }

    void build(const string &s) {
        for (auto c : s)
            build(c);
    }

    void build(char *s, int n) {
        for (int i = 0; i < n; ++i)
            build(s[i]);
    }

    /*工具函数*/

    /**
     * 计算 linkD 数组
     */
    void parentTreeDegree() {
        memset(linkD, 0, sizeof(int) * tot);
        for (int i = 0; i < tot; ++i)
            linkD[link[i]]++;
    }

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
     * 计算 sizeC 数组（使用队列解决）
     * 效率高但是没有其他作用
     */
    void getSizeQueue() {
        parentTreeDegree();
        queue<int> q;
        for (int i = 0; i < tot; ++i) if (linkD[i] == 0) q.push(i);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            sizeC[link[cur]] += sizeC[cur];
            if (--linkD[link[cur]] == 0 && link[cur] != 0) q.push(link[cur]);
        }
    }

    /**
     * 计算 sizeC 数组（使用基数排序解决）
     * ！！！请先调用 sortLen ！！！
     * 效率略低但是同时可以计算出 lenSorted 数组
     */

    void getSizeLen() {
        for (int i = tot - 2; i >= 0; --i)
            sizeC[link[lenSorted[i]]] += sizeC[lenSorted[i]];
    }

    /**
     * 计算 count 数组
     * ！！！请先调用 sortLen ！！！
     */
    void getCount() {
        for (int i = tot - 2; i >= 0; --i) {
            count[lenSorted[i]] = 1;
            for (int j = 0; j < 26; ++j)
                count[lenSorted[i]] += next[lenSorted[i]][j] ? count[next[lenSorted[i]][j]] : 0;
        }
    }

    /**
     * 检测字符串 s 是否是原串的子串
     * @param s 字符串
     * @return 字符串 s 最终匹配的节点，如果中途失配，则返回 -1，否则返回非负整数
     */
    int check(const string &s) {
        int cur = 0;
        for (auto c : s) {
            if (next[cur][c - 'a']) cur = next[cur][c - 'a'];
            else return -1;
        }
        return cur;
    }

    /**
     * 求整个字符串中，有多少个不同的字串
     * @return 字串个数
     */
    int sumCount() {
        int res = 0;
        for (int i = 1; i < tot; ++i)
            res += len[i] - len[link[i]];
        return res;
    }

    /**
     * 求算两个字符串的最长公共子串（连续）
     * @param s 另一个字符串
     * @param endPos (ref)求算的公共子串的最终位置，不包含
     * @return 公共子串的长度，实际公共子串的下标为 [endPos - return, endPos)
     */
    int LCS(const string &s, int &endPos) {
        int cur = 0, curLen = 0, maxLen = 0;
        for (int i = 0; i < s.size(); ++i) {
            while (!next[cur][s[i] - 'a'] && link[cur] != -1) {
                cur = link[cur];
                curLen = len[cur];
            }
            if (next[cur][s[i] - 'a']) {
                cur = next[cur][s[i] - 'a'];
                curLen++;
                if (curLen > maxLen) {
                    maxLen = curLen;
                    endPos = i + 1;
                }
            }
        }
        return maxLen;
    }

    void debug() {
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
} sam;
