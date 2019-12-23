#include <bits/stdc++.h>
using namespace std;
/******************************************
 * 1、优先队列的排序设定
 * 默认：大的优先
 ******************************************/
struct node {
    int a, b;
    bool operator<(const node &other) const {
        return a > b;
    }
};
struct cmp {
    bool operator()(const node &x, const node &y) const {
        return x.b > y.b;
    }
};
priority_queue<node> pq;                    // 需要在结构体内重载 < 运算符
priority_queue<node, vector<node>, cmp> pq; // 需要定义一个运算

/******************************************
 * 2、二分匹配查找
 ******************************************/
vector<int> v;
binary_search(v.begin(), v.end(), 1);
/*
 * 检查等价于 value 的元素是否出现于范围 [first, last) 中。
 */
equal_range(v.begin(), v.end(), 1);
/*
 * 返回含有定义所需范围的一对迭代器的 std::pair ，第一迭代器指向首个不小于 value 的元素，而第二迭代器指向首个大于 value 的元素。
 * 若无元素小于 value ，则 last 作为第一元素返回。类似地，若无元素大于 value ，则 last 作为第二元素返回。
 */
lower_bound(v.begin(), v.end(), 1);
/*
 * 返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器，或若找不到这种元素则返回 last 。
 */
upper_bound(V.begin(), v.end(), 1);
/*
 * 返回指向范围 [first, last) 中首个大于 value 的元素的迭代器，或若找不到这种元素则返回 last 。
 */
int arr[] = {3, 2, 1};
cout << "用prev_permutation对3 2 1的全排列" << endl;
do {
    cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';
} while (prev_permutation(arr, arr + 3)); // 获取上一个较大字典序排列，如果3改为2，只对前两个数全排列

int arr1[] = {1, 2, 3};
cout << "用next_permutation对1 2 3的全排列" << endl;
do {
    cout << arr1[0] << ' ' << arr1[1] << ' ' << arr1[2] << '\n';
} while (next_permutation(arr1, arr1 + 3)); // 获取下一个较大字典序排列，如果3改为2，只对前两个数全排列
/**
 * 全排列
 * 注意数组顺序，必要时要对数组先进行排序
 */
