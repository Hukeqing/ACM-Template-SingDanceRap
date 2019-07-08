/*
 * 最大流 SAP 算法，用 GAP 优化后
 * 先把流量限制赋值到 maps 数组
 * 然后调用 SAP 函数求解
 */

#define MAXN 222
#define inf 100000000 + 1000
int maps[MAXN][MAXN]; //存图
int pre[MAXN];        //记录当前点的前驱
int level[MAXN];      //记录距离标号
int gap[MAXN];        //gap常数优化

//入口参数vs源点，vt汇点
int SAP(int vs, int vt)
{
    memset(pre, -1, sizeof(pre));
    memset(level, 0, sizeof(level));
    memset(gap, 0, sizeof(gap));
    gap[0] = vt;
    int v, u = pre[vs] = vs, maxflow = 0, aug = inf;

    while (level[vs] < vt)
    {
        //寻找可行弧
        for (v = 1; v <= vt; v++)
        {
            if (maps[u][v] > 0 && level[u] == level[v] + 1)
            {
                break;
            }
        }
        if (v <= vt)
        {
            pre[v] = u;
            u = v;
            if (v == vt)
            {
                int neck = 0;
                aug = inf;
                //寻找当前找到的一条路径上的最大流 , (瓶颈边)
                for (int i = v; i != vs; i = pre[i])
                {
                    if (aug > maps[pre[i]][i])
                    {
                        aug = maps[pre[i]][i];
                        neck = i;
                    }
                }
                maxflow += aug;
                //更新残留网络
                for (int i = v; i != vs; i = pre[i])
                {
                    maps[pre[i]][i] -= aug;
                    maps[i][pre[i]] += aug;
                }
                u = vs; //从源点开始继续搜
                        //		u=neck; 	  // Dnic 多路增广优化，下次增广时，从瓶颈边(后面)开始
            }
        }
        else
        {
            //找不到可行弧
            int minlevel = vt;
            //寻找与当前点相连接的点中最小的距离标号
            for (v = 1; v <= vt; v++)
            {
                if (maps[u][v] > 0 && minlevel > level[v])
                {
                    minlevel = level[v];
                }
            }
            gap[level[u]]--; //(更新gap数组）当前标号的数目减1；
            if (gap[level[u]] == 0)
                break; //出现断层
            level[u] = minlevel + 1;
            gap[level[u]]++;
            u = pre[u];
        }
    }
    return maxflow;
}