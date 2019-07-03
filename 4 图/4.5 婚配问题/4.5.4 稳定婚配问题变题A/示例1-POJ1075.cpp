/*
 * http://poj.org/problem?id=1075
 * 大致题意
 * 学校招生，本地学生优先。N个学生，M个学校。学生i，Ri学生的区域号，Mi分数，K志愿学校数，Fi1第一志愿，FiK第k志愿。学校i，Ri学校区域号，Ci学校i的容量。
 *
 * 招生规定：
 * 学生A、B在相同志愿报了同一学校。A是外地，B是本地。A的分数*0.7于B的分数比较，择优录取。
 * 按志愿顺序录取。
 */

// AC code
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <string>

using namespace std;
/*
 * 稳定婚配问题变题
 * 1、男女人数不同
 * 2、男生可以仅对部分女主有好感
 * 3、女生对男生的好感度可以通过公式计算
 * 4、男生可以有匹配失败（女生未确定）
 * 5、可以多个男生匹配同一个女生
 * 
 * 使用说明：
 * 补充 cmp 内的重载函数
 * 补充变量 boyRankList、num、limit
 * 调用函数 findMatch
 * 结果保存在 boyMatch 中，如果等于 -1 则此男生匹配失败
 */
const int MAXN = 160;

struct boy // 男主的属性——用于计算好感度，必须包含变量 id，用于标记男生的位置
{
    int id;
    int loc, grade, nowf;
    boy() {}
    boy(int i, int lo, int gr, int no)
    {
        this->id = i;
        this->loc = lo;
        this->grade = gr;
        this->nowf = no;
    }
};

struct cmp // 每一个男生的好感度计算公式，优先者在前返回 true
{
    bool operator()(boy x, boy y)
    {
        if ((x.loc == x.nowf && y.loc == y.nowf) || (x.loc != x.nowf && y.loc != y.nowf))
            return x.grade > y.grade;
        int xx = x.loc == x.nowf ? x.grade * 10 : x.grade * 7;
        int yy = y.loc == y.nowf ? y.grade * 10 : y.grade * 7;
        if (xx != yy)
            return xx > yy;
        return x.loc == x.nowf;
    }
};
int boyRankList[MAXN][MAXN]; // 男生 i 第 j 个喜欢的女生是几号
int num[MAXN];               // 第 i 个男生喜欢的女生个数
int limit[MAXN];             // 第 i 个女生可以同时对多少个男生
int boyMatch[MAXN];
priority_queue<boy, vector<boy>, cmp> girlMatch[MAXN]; // 女生的好感度队列
int manpos[MAXN];
queue<int> q;
boy a[MAXN];
int n, m;
int r[MAXN];                // 保存学校地区

void findMatch()
{
    while (!q.empty())
        q.pop();
    for (int i = 1; i <= n; ++i)
    {
        q.push(i);
        boyMatch[i] = -1;
        manpos[i] = 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        while (!girlMatch[i].empty())
            girlMatch[i].pop();
    }
    while (!q.empty())
    {
        int s = q.size();
        for (int i = 1; i <= s; ++i)
        {
            int now = q.front();
            q.pop();
            ++manpos[now];
            if (manpos[now] > num[now])
                continue;
            int wanna = boyRankList[now][manpos[now]];
            if (girlMatch[wanna].size() < limit[wanna])
            {
                /* 
                 * 在此处 new 一个 boy（非指针），要求如下
                 * id = now
                 * 其他属性应与 a[new] 相同，如有必要可以修改成其他的
                 */
                boy x = *new boy(now, a[now].loc, a[now].grade, r[wanna]);
                girlMatch[wanna].push(x);
                boyMatch[now] = wanna;
            }
            else
            {
                if (limit[wanna] > 0)
                {
                    boy y = girlMatch[wanna].top();
                    /* 
                     * 在此处 new 一个 boy（非指针），要求如下
                     * id = now
                     * 其他属性应与 a[new] 相同，如有必要可以修改成其他的
                     */
                    boy x = *new boy(now, a[now].loc, a[now].grade, r[wanna]);
                    if (x.grade > y.grade)
                    {
                        girlMatch[wanna].pop();
                        girlMatch[wanna].push(x);
                        boyMatch[now] = wanna;
                        boyMatch[y.id] = -1;
                        q.push(y.id);
                    }
                    else
                        q.push(now);
                }
                else
                    q.push(now);
            }
        }
    }
}

int main()
{
#ifdef ACM_LOCAL
    freopen("./in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].loc >> a[i].grade;
            a[i].id = i;
            cin >> num[i];
            for (int j = 1; j <= num[i]; ++j)
                cin >> boyRankList[i][j];
        }
        for (int i = 1; i <= m; ++i)
            cin >> r[i] >> limit[i];
        findMatch();
        for (int i = 1; i <= n; ++i)
        {
            if (boyMatch[i] == -1)
                cout << "not accepted" << endl;
            else
                cout << boyMatch[i] << endl;
        }
        cout << endl;
    }
    return 0;
}