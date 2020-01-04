/*
 * AC 自动机：多个模式串去匹配一个串，求有多少个模式串与主串有匹配内容
 *
 * 使用操作：
 * 1、先构建树
 * 2、使用函数 init
 * 3、把每一个模式串插入到树中 insert
 * 4、使用 query 询问有多少个模式串匹配
 * 
 * Debug 仅做测试使用
 */

const int CHAR_NUM = 26;//仅小写
const int MAXN = 500;//模式串个数
const int MAXM = 200;//模式串最长长度
const int NUM = MAXN * MAXM;//空间=个数*长度，稳

struct Trie {
    int next[NUM][CHAR_NUM], fail[NUM], end[NUM];
    int root, L;

    int newNode() {
        for (int i = 0; i < CHAR_NUM; i++)
            next[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }

    void reset() {
        for (int i = 0; i < L; i++) {
            fail[i] = end[i] = 0;
            memset(next[i], -1, sizeof(next[i]));
        }
        L = 0;
        root = newNode();
    }

    void insert(char *buf) {
        int len = (int) strlen(buf);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (next[now][buf[i] - 'a'] == -1)
                next[now][buf[i] - 'a'] = newNode();
            now = next[now][buf[i] - 'a'];
        }
        end[now]++;
    }

    void build() {
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < CHAR_NUM; i++)
            if (next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i = 0; i < CHAR_NUM; i++) {
                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
    }

    int query(char *buf) {
        int len = (int) strlen(buf);
        int now = root;
        int res = 0;
        for (int i = 0; i < len; i++) {
            now = next[now][buf[i] - 'a'];
            int temp = now;
            while (temp != root) {
                res += end[temp];
                end[temp] = 0;
                temp = fail[temp];
            }
        }
        return res;
    }
};