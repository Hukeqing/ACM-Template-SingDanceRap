#include<bits/stdc++.h>

#define NUM 4001000
using namespace std;
#define ll long long
#define ull unsigned long long

/**
 * 马拉车
 * @param s 原串
 * @param len 原串长度
 * @param ma 辅助数组
 * @param mp 长度记录数组
 */
void manacher(const string &s, int len, char *ma, int *mp) {
    int l = 0;
    ma[l++] = '$';
    ma[l++] = '#';
    for (int i = 0; i < len; i++) {
        ma[l++] = s[i];
        ma[l++] = '#';
    }
    ma[l] = 0;
    int mx = 0, id = 0;
    for (int i = 0; i < l; i++) {
        mp[i] = mx > i ? (mp[2 * id - i] < mx - i ? mp[2 * id - i] : mx - i) : 1;
        while (ma[i + mp[i]] == ma[i - mp[i]]) mp[i]++;
        if (i + mp[i] > mx) {
            mx = i + mp[i];
            id = i;
        }
    }
}
/*
 * example：abaaba
 * i:       0  1  2  3  4  5  6  7  8  9 10 11 12 13
 * Ma[i]:   $  #  a  #  b  #  a  #  a  #  b  #  a  #
 * Mp[i]:   1  1  2  1  4  1  2  7  2  1  4  1  2  1
 * Mp[i] - 1：为以该点为中心的回文串长度。
 */

string s;
/**开原串的两倍长度**/
char ma[NUM * 2];
int mp[NUM * 2];
/****/
/**
 * 0：记录每个点作为左中心的偶数串信息；1：记录每个点作为中心的奇数串信息
 */
int len[NUM][2]; // 长度
int l[NUM][2];  // 左边界，闭区间
int r[NUM][2];  // 右边界，闭区间

int main() {
#ifdef ACM_LOCAL
    freopen("../std.in", "r", stdin);
#endif
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        int sz = s.size();
        memset(ma, 0, sizeof(char) * (sz * 2 + 10));
        memset(mp, 0, sizeof(int) * (sz * 2 + 10));
        memset(len[0], 0, sizeof(int) * (sz * 2 + 10));
        manacher(s, sz, ma, mp);
        for (int i = 0; i < sz; i++) {
            len[i][0] = mp[i * 2 + 3] - 1;
            if (len[i][0] == 0) {
                l[i][0] = r[i][0] = -1;
            } else {
                l[i][0] = i - len[i][0] / 2 + 1;
                r[i][0] = i + len[i][0] / 2;
            }
            len[i][1] = mp[i * 2 + 2] - 1;
            l[i][1] = i - len[i][1] / 2;
            r[i][1] = i + len[i][1] / 2;
        }
    }
    return 0;
}
