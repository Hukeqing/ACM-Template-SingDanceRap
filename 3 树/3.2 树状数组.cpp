#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#ifdef ACM_LOCAL
const ll MAXN = 500100;
#endif
#ifndef ACM_LOCAL
const ll MAXN = 500100;
#endif

/**
 *树状数组
 */
struct BT {
    /**
     * 1=(001)      C[1]=A[1];
     * 2=(010)      C[2]=A[1]+A[2];
     * 3=(011)      C[3]=A[3];
     * 4=(100)      C[4]=A[1]+A[2]+A[3]+A[4];
     * 5=(101)      C[5]=A[5];
     * 6=(110)      C[6]=A[5]+A[6];
     * 7=(111)      C[7]=A[7];
     * 8=(1000)     C[8]=A[1]+A[2]+A[3]+A[4]+A[5]+A[6]+A[7]+A[8];
     */
    int C[MAXN], n;

    /**
     * 求出最低位为1的值
     * @param t
     * @return
     */
    static int lowbit(int t) {
        return t & (-t);
    }

    /**
     * 区间求和
     * @param x
     * @return 和
     */
    int sum(int x) {
        int ans = 0;
        for (int i = x; i; i -= lowbit(i))
            ans += C[i];
        return ans;
    }

    /**
     * 求[l, r]之间的区间和
     * @param l 左边界
     * @param r 右边界
     * @return 和
     */
    int sumOfRange(int l, int r){
        return sum(r) - sum(l - 1);
    }

    /**
     * 单点修改 增加y
     * @param x 修改位置
     * @param y 增加的值
     */
    void add(int x, int y) {
        for (int i = x; i <= n; i += lowbit(i))
            C[i] += y;
    }

    /**
     * 重置
     */
    void reset() {
        memset(C, 0, sizeof(C));
        n = 0;
    }

    BT(int n) {
        this->n = n;
        memset(C, 0, sizeof(C));
    }

    BT() {}

	/**
	 * 重置n
	 */
    void setN(int x) {
        this->n = x;
    }
};

BT bt = BT(0);

int main() {
    int n, m;
    while(cin >> n >> m) {
        bt.setN(n);
        int x, y, z;
        for (int i = 0; i < n; i++) {
            cin >> x;
            bt.add(i + 1, x);
        }
        while (m--) {
            cin >> x >> y >> z;
            if (x == 1)
                bt.add(y, z);
            else if (x == 2)
                cout << bt.sumOfRange(y, z) << endl;
        }
        bt.reset();
    }
    return 0;
}