#include <bits/stdc++.h>
using namespace std;
/*
 * 1、优先队列的排序设定
 * 默认：大的优先
 */
struct node
{
    int a, b;
    bool operator<(const node &other) const
    {
        return a > b;
    }
};
struct cmp
{
    bool operator()(const node &x, const node &y) const
    {
        return x.b > y.b;
    }
};
priority_queue<node> pq;                    // 需要在结构体内重载 < 运算符
priority_queue<node, vector<node>, cmp> pq; // 需要定义一个运算
