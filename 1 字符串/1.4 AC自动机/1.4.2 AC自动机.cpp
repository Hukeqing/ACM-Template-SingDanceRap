/*
 * AC 自动机：多个模式串去匹配一个串，求有多少个模式串与主串有匹配内容
 *
 * 使用操作：
 * 1、把每一个模式串插入到树中 insert
 * 2、build
 * 3、使用 query 询问有多少个模式串匹配
 */

const int CHAR_NUM = 26;//仅小写
const int MAXN = 50;//模式串个数
const int MAXM = 100010;//模式串最长长度
const int NUM = MAXN * MAXM;//空间=个数*长度

struct Trie {
    int c[NUM][CHAR_NUM], val[NUM], fail[NUM], cnt;

    void insert(char *s) {
        int len = strlen(s);
        int now = 0;
        for (int i = 0; i < len; i++) {
            int v = s[i] - 'a';
            if (!c[now][v])c[now][v] = ++cnt;
            now = c[now][v];
        }
        val[now]++;
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < CHAR_NUM; i++)if (c[0][i])fail[c[0][i]] = 0, q.push(c[0][i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < CHAR_NUM; i++)
                if (c[u][i])fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
                else c[u][i] = c[fail[u]][i];
        }
    }

    int query(char *s) {
        int len = strlen(s);
        int now = 0, ans = 0;
        for (int i = 0; i < len; i++) {
            now = c[now][s[i] - 'a'];
            for (int t = now; t && ~val[t]; t = fail[t])ans += val[t], val[t] = -1;
        }
        return ans;
    }
} AC;
