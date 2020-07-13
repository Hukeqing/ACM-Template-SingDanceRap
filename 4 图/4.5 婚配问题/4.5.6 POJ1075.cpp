/*
 * http://poj.org/problem?id=1075
 * 大致题意
 * 学校招生，本地学生优先。N个学生，M个学校。学生i，Ri学生的区域号，Mi分数，K志愿学校数，Fi1第一志愿，FiK第k志愿。学校i，Ri学校区域号，Ci学校i的容量。
 *
 * 招生规定：
 * 学生A、B在相同志愿报了同一学校。A是外地，B是本地。A的分数*0.7与B的分数比较，择优录取。
 * 按志愿顺序录取。
 * ****输入
 * 输入的第一行包含一个整数t（1 <= t <= 10），
 * 测试用例的数量，后跟每个测试用例的输入数据。
 * 每个测试用例的第一行包含N（1 <= N <= 150）
 * 和M（1 <= M <= 50），其后是N行，每行一个学生。
 * 这些行的格式依次为Ri，Mi，K，Fi1，...，FiK。
 * 在此行中，即学生i，Ri是他/她的地区号码，Mi是他/她的入学考试分数，
 * K是他/她的优先级列表中的FDU数量（0 <= K <= M） ，
 * 以及按照兴趣顺序包含FDU编号的优先级列表。然后有M条线，
 * 每个FDU一条。每行依次包含Ri和Ci，分别是Fi的区域号（第i个FDU）和Fi的容量。
 * 注意，区域号是任意整数。
 * ****输出
 * 不同测试用例的输出仅由一个空白行分隔。对于每个测试用例，您应该编写N行，
 * 每N个学生一个。如果学生i已被FDU Fj录取，则第i行应包含j，
 * 并且如果该学生未因其兴趣而被FDU Fj录取，则该行应不被接受。
 * ****样例输入
1
9 2
1 100 2 1 2
2 80 2 2 1
1 90 1 1
2 40 1 2
2 50 1 1
1 60 1 2
2 75 1 1
1 95 1 1
2 30 1 2
1 3
2 4
 *　****样例输出
1
2
1
2
not accepted
2
not accepted
1
2
 */

// AC code
#include <bits/stdc++.h>

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

struct boy { // 男主的属性——用于计算好感度，必须包含变量 id，用于标记男生的位置
    int id;
    int loc, grade, nowf;
    boy() {}
    boy(int i, int lo, int gr, int no) {
        this->id = i;
        this->loc = lo;
        this->grade = gr;
        this->nowf = no;
    }
};

struct cmp { // 每一个男生的好感度计算公式，优先者在前返回 true
    bool operator()(boy x, boy y) {
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
int r[MAXN]; // 保存学校地区

void findMatch() {
    while (!q.empty())
        q.pop();
    for (int i = 1; i <= n; ++i) {
        q.push(i);
        boyMatch[i] = -1;
        manpos[i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        while (!girlMatch[i].empty())
            girlMatch[i].pop();
    }
    while (!q.empty()) {
        int s = q.size();
        for (int i = 1; i <= s; ++i) {
            int now = q.front();
            q.pop();
            ++manpos[now];
            if (manpos[now] > num[now])
                continue;
            int wanna = boyRankList[now][manpos[now]];
            if (girlMatch[wanna].size() < limit[wanna]) {
                /*
                 * 在此处 new 一个 boy（非指针），要求如下
                 * id = now
                 * 其他属性应与 a[new] 相同，如有必要可以修改成其他的
                 */
                boy x = *new boy(now, a[now].loc, a[now].grade, r[wanna]);
                girlMatch[wanna].push(x);
                boyMatch[now] = wanna;
            } else {
                if (limit[wanna] > 0) {
                    boy y = girlMatch[wanna].top();
                    /*
                     * 在此处 new 一个 boy（非指针），要求如下
                     * id = now
                     * 其他属性应与 a[new] 相同，如有必要可以修改成其他的
                     */
                    boy x = *new boy(now, a[now].loc, a[now].grade, r[wanna]);
                    if (x.grade > y.grade) {
                        girlMatch[wanna].pop();
                        girlMatch[wanna].push(x);
                        boyMatch[now] = wanna;
                        boyMatch[y.id] = -1;
                        q.push(y.id);
                    } else
                        q.push(now);
                } else
                    q.push(now);
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].loc >> a[i].grade;
            a[i].id = i;
            cin >> num[i];
            for (int j = 1; j <= num[i]; ++j)
                cin >> boyRankList[i][j];
        }
        for (int i = 1; i <= m; ++i)
            cin >> r[i] >> limit[i];
        findMatch();
        for (int i = 1; i <= n; ++i) {
            if (boyMatch[i] == -1)
                cout << "not accepted" << endl;
            else
                cout << boyMatch[i] << endl;
        }
        cout << endl;
    }
    return 0;
}
