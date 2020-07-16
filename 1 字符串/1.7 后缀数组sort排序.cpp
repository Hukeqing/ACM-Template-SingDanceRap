#define MAXN 1000100

/**
 * beSort 是被排序数组，表示排序后第 i 小的后缀是以 beSort[i] 的位置作为后缀起点
 * ra 是每个字符串的 rank，ra[i][nxt] 表示第 i 个字符作为后缀开始位置的字符串的第 ra[i][nxt] 小
 */

int beSort[MAXN], ra[MAXN << 1][2];

void sa(const string& s) {
    for (int i = 0; i < s.size(); ++i) {
        beSort[i] = i;
        ra[i][0] = s[i];
    }
    int cur = 0, nxt = 1;
    for (unsigned offset = 1; offset < s.size(); offset <<= 1u) {
        sort(beSort, beSort + s.size(), [&](int a, int b) {
            return ra[a][cur] == ra[b][cur] ?
                   ra[a + offset][cur] < ra[b + offset][cur] :
                   ra[a][cur] < ra[b][cur];
        });

        int curRank = 0;
        ra[beSort[0]][nxt] = 0;
        for (int i = 1; i < s.size(); ++i)
            ra[beSort[i]][nxt] = (ra[beSort[i]][cur] == ra[beSort[i - 1]][cur] &&
                                  ra[beSort[i] + offset][cur] == ra[beSort[i - 1] + offset][cur])
                                 ? curRank : ++curRank;
        swap(cur, nxt);
    }
}
