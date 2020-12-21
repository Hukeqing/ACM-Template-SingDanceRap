#include<bits/stdc++.h>

#define NUM 30010
using namespace std;
#define ll long long

string s[NUM];
int n;
struct Trie {
    /**
     * 所有字符串的总size * 0.84
     */
    static const int CHAR_SIZE = 250010;
    /**
     * 字符集size + 1
     */
    static const int CHARSET_SIZE = 27;
    int cnt[CHAR_SIZE];
    int son[CHAR_SIZE][CHARSET_SIZE];
    int tot;

    /**
     * 初始化计数数组、子节点数组、开点tot
     */
    void init() {
        tot = 2;
        memset(cnt, 0, sizeof(int) * CHAR_SIZE);
        memset(son, 0, sizeof(int) * (CHAR_SIZE * CHARSET_SIZE));
    }

    /**
     * 将指定下标的串插入到字典树中，并计数
     * @param idx 下标
     * @param v 个数
     */
    void add(int idx, int v) {
        int root = 1;
        cnt[root] += v;
        for (auto i : s[idx]) {
            if (!son[root][i - 'a']) {
                son[root][i - 'a'] = tot++;
            }
            cnt[son[root][i - 'a']] += v;
            root = son[root][i - 'a'];
        }
    }

    /**
     * 在字典树中查看某串是否存在
     * @param idx
     * @return
     */
    bool find(string * tmp) {
        int root = 1;
        for (auto i : *tmp) {
            if (!cnt[son[root][i - 'a']]) return false;
            root = son[root][i - 'a'];
        }
        return true;
    }
} trie;

int main() {
#ifdef ACM_LOCAL
    freopen("../std.in", "r", stdin);
#endif
    trie.init();
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    for (int i = 0; i < n; i++)
        trie.add(i, 1);
    string tmp = "abcd";
    cout << trie.find(&tmp);
    return 0;
}
