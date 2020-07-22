/**
 *  扩展后缀自动机——后缀自动机在字典树上的扩展
 *  性质同普通自动机
 *  同时可以对多个串处理
 */


#define MAXN 2000000            // 双倍字符串长度
#define CHAR_NUM 30             // 字符集个数，注意修改下方的 (-'a')

struct exSAM {
    int len[MAXN];              // 节点长度
    int link[MAXN];             // 后缀链接，link
    int next[MAXN][CHAR_NUM];   // 转移
    int tot;                    // 节点总数：[0, tot)

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
        if (next[cur][c]) return next[cur][c];
        return next[cur][c] = tot++;
    }

    void insert(const string &s) {
        int root = 0;
        for (auto ch : s) root = insertTrie(root, ch - 'a');
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
