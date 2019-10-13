#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int CHAR_NUM = 26;//ascii字符
#ifdef ACM_LOCAL
const int NUM = 100000;
#else
const int NUM = 200000;
#endif

struct SAM {
    int len[NUM * 2]; //最长子串的长度(该节点子串数量=len[x]-len[link[x]])
    int fa[NUM * 2];   //后缀链接(最短串前部减少一个字符所到达的状态)
    int ch[NUM * 2][CHAR_NUM];  //状态转移(尾部加一个字符的下一个状态)(图)
    int tot;    //结点编号
    int last;    //最后结点

    /**
     * 初始化
     */
    void init() {
        for (int i = 1; i <= tot; i++)
            fa[i] = len[i] = 0, memset(ch[i], 0, sizeof(ch[i]));
        last = tot = 1; //1表示root起始点 空集
    }

    /**
     * 将字符c添加进自动机
     * @param c 目标字符
     */
    void extend(int c) {     //插入字符，为字符ascll码值
        int x = ++tot; //创建一个新结点x;
        len[x] = len[last] + 1; //  长度等于最后一个结点+1
        //num[x] = 1;  //接受结点子串除后缀连接还需加一
        int p;  //第一个有C转移的结点;
        for (p = last; p && !ch[p][c]; p = fa[p])
            ch[p][c] = x;//沿着后缀连接 将所有没有字符c转移的节点直接指向新结点
        if (!p)fa[x] = 1;
        else {
            int q = ch[p][c];    //p通过c转移到的结点
            if (len[p] + 1 == len[q])    //pq是连续的
                fa[x] = q;
            else {
                int nq = ++tot;   //不连续 需要复制一份q结点
                len[nq] = len[p] + 1;   //令nq与p连续
                fa[nq] = fa[q];   //因后面link[q]改变此处不加cnt
                memcpy(ch[nq], ch[q], sizeof(ch[q]));  //复制q的信息给nq
                for (; p && ch[p][c] == q; p = fa[p])
                    ch[p][c] = nq;    //沿着后缀连接 将所有通过c转移为q的改为nq
                fa[q] = fa[x] = nq; //将x和q后缀连接改为nq

            }
        }
        last = x;  //更新最后处理的结点
    }

    /**
     * 求自动机中不相同子串数量
     * @return 不相同子串数量
     */
    ll getSubNum() {
        ll ans = 0;
        for (int i = 2; i <= tot; i++)
            ans += len[i] - len[fa[i]];   //一状态子串数量等于len[i]-len[link[i]]
        return ans;
    }

    /**
     * 获取s的匹配节点
     * @param s 目标字符串
     * @return 匹配节点编号
     */
    int getPos(string &s) {
        int index = 0;
        int i = 1;
        int size = s.length();
        for (index = 0; index < size; index++)
            i = ch[i][s[index] - 'a'];

        return i;
    }

} sam;