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
 * 补充变量 n、m、boyRankList、num、limit
 * 调用函数 findMatch
 * 结果保存在 boyMatch 中，如果等于 -1 则此男生匹配失败
 */
const int MAXN = 160;

struct boy // 男主的属性——用于计算好感度，必须包含变量 id，用于标记男生的位置
{
    int id;
    boy() {}
    boy(int i)
    {
        this->id = i;
    }
};

struct cmp // 每一个男生的好感度计算公式，优先者在前返回 true
{
    bool operator()(boy x, boy y)
    {
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
int n, m; // 男生人数、女生人数

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
