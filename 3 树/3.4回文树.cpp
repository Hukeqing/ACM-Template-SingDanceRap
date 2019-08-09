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