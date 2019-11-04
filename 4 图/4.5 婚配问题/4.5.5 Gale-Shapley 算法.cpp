/*
 * Gale-Shapley 算法
 * 男女相互有好感度排行时的稳定婚配
 * 二分图格式：左男右女
 * 先在数组 b、g 中存入数据
 * 然后运行函数 Gale_Shapley 
 * 结果保存在 bo、gi 两个数组中
 * 在男女人数相同的时候确认可以用
 */

const int MAXN = "Edit";

int n;                  // 男生的个数
int b[MAXN][MAXN];      // 男生 i 第 j 个喜欢的女生是几号
int g[MAXN][MAXN];      // 女生 i 对男生 j 的排名
int by[MAXN], gl[MAXN]; // 匹配情况
int r[MAXN];
void Gale_Shapley() {
    memset(by, 0, sizeof(by));
    memset(gl, 0, sizeof(gl));
    for (size_t i = 0; i <= n; i++)
        r[i] = 1;

    int flag, t;
    while (1) {
        flag = 1;
        for (int i = 1; i <= n; i++) // 编号起始值
            if (!by[i]) {
                t = b[i][r[i]++]; // t 是 他喜欢的女生且他还没有匹配过
                if (!gl[t])       // 如果这个女生刚好没对象，就结成一对
                {
                    by[i] = t;
                    gl[t] = i;
                } else if (g[t][gl[t]] > g[t][i]) // 如果她有对象了，但是她更喜欢当前这个男生，则女生抛弃之前的男生和这个结成一对
                {
                    by[gl[t]] = 0;
                    gl[t] = i;
                    by[i] = t;
                }
                flag = 0;
            }
        if (flag)
            break;
    }
}