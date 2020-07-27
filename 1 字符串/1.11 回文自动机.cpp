#include<bits/stdc++.h>

#define CHAR_NUM 30
using namespace std;

typedef long long ll;

#ifdef ACM_LOCAL
const ll NUM = 100;
#else
const ll NUM = 301000;
#endif

char str[NUM];
ll cnt = 0;//统计不同回文串的个数，即等同于回文树的节点数-1（不包括0节点）
int last, tot;

struct Pam {

    /**
     * 对应串的长度
     */
    int len;
    /**
     * 失配节点
     */
    int fail;
    /**
     * 子节点
     */
    int son[CHAR_NUM];

} pam[NUM];

/**
 * 初始化
 */
void init() {
    memset(pam, 0, sizeof(pam));
    pam[0].len = 0;
    pam[0].fail = 1;
    pam[1].len = -1;
    tot = 2;
    cnt = 0;
}

/**
 * 获取从now节点开始匹配到尾缀为str[index]回文串的节点
 * @param now 待匹配节点
 * @param index 匹配字符串的下标
 * @return 匹配节点编号
 */
int get(int now, int index) {
    while (str[index] != str[index - pam[now].len - 1])
        now = pam[now].fail;
    return now;
}

/**
 * 添加一个str中index位置上的字符，更新回文树
 * @param index 指定字符位置
 */
void add(int index) {
    int u = get(last, index);
    int ch = str[index] - 'a';
    if (pam[u].son[ch] == 0) {
        int v = tot++;
        pam[v].len = pam[u].len + 2;
        pam[v].fail = pam[get(pam[u].fail, index)].son[ch];
        pam[u].son[ch] = v;
        cnt++;
    }

    //更新上次访问节点
    last = pam[u].son[ch];
}

int main() {
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    for(int i = 0;i < t;i++) {
        init();
        cout << "Case #" << i + 1 << ": ";
        cin >> str;
        int size = strlen(str);
        for (int j = 0; j < size; j++)
            add(j);

        cout << cnt << endl;
    }

    return 0;

}


#define MAXN 10000
#define CHAR_NUM 30             // 字符集个数，注意修改下方的 (-'a')

struct EER {
    int len[MAXN];
    int link[MAXN];
    int next[MAXN][CHAR_NUM];
    int last;
    int tot;

    int sizeC[MAXN];

    void init() {
        last = 1;
        tot = 2;
        link[0] = len[0] = -1;
        link[1] = len[1] = 0;
        sizeC[0] = sizeC[1] = 0;
    }

    void build(const string &s) {
        for (int i = 0; i < s.size(); ++i) {
            int p = last, curLen;
            while (true) {
                curLen = len[p];
                if (i - curLen - 1 >= 0 && s[i - curLen - 1] == s[i])
                    break;
                p = link[p];
            }
            if (next[p][s[i] - 'a']) {
                last = next[p][s[i] - 'a'];
                continue;
            }
            last = tot++;
            len[last] = len[p] + 2;
            next[p][s[i] - 'a'] = last;

            if (len[last] == 1) {
                link[last] = 1;
                sizeC[last] = 1;
                continue;
            }

            while (true) {
                p = link[p];
                curLen = len[p];
                if (i - curLen - 1 >= 0 && s[i - curLen - 1] == s[i]) {
                    link[last] = next[p][s[i] - 'a'];
                    break;
                }
            }
            sizeC[last] = sizeC[link[last]] + 1;
        }
    }

    void reset() {
        memset(next, 0, sizeof(next));
    }

    void debug() {
        cout << "     i      link       ";
        for (int i = 0; i < 26; ++i)
            cout << setw(3) << (char) (i + 'a');
        cout << endl;
        for (int i = 0; i < tot; ++i) {
            cout << "i: " << setw(3) << i
                 << " link: " << setw(3) << link[i]
                 << " next: ";
            for (int j = 0; j < CHAR_NUM; ++j)
                cout << setw(3) << next[i][j];
            cout << endl;
        }
    }
} eer;
