/**
 * 
 */
#define MAXN 10000
#define CHAR_NUM 30             // 字符集个数，注意修改下方的 (-'a')

struct EER {
    int len[MAXN];
    int link[MAXN];
    int next[MAXN][CHAR_NUM];
    int last;
    int tot;

    int sizeC[MAXN];

    void init() {
        last = 1;
        tot = 2;
        link[0] = len[0] = -1;
        link[1] = len[1] = 0;
        memset(next[0], 0, sizeof(next[0]));
        memset(next[1], 0, sizeof(next[1]));
    }

    void build(const string &s) {
        for (int i = 0; i < s.size(); ++i) {
            int p = last, curLen;
            while (true) {
                curLen = len[p];
                if (i - curLen - 1 >= 0 && s[i - curLen - 1] == s[i])
                    break;
                p = link[p];
            }
            if (next[p][s[i] - 'a']) {
                last = next[p][s[i] - 'a'];
                continue;
            }
            last = tot++;
            len[last] = len[p] + 2;
            memset(next[last], 0, sizeof(next[last]));
            next[p][s[i] - 'a'] = last;

            if (len[last] == 1) {
                link[last] = 1;
                sizeC[last] = 1;
                continue;
            }

            while (true) {
                p = link[p];
                curLen = len[p];
                if (i - curLen - 1 >= 0 && s[i - curLen - 1] == s[i]) {
                    link[last] = next[p][s[i] - 'a'];
                    break;
                }
            }
            sizeC[last] = sizeC[link[last]] + 1;
        }
    }

    void build(char *s, int n) {
        for (int i = 0; i < n; ++i) {
            int ch = s[i] - 'a';
            int p = last, curLen;
            while (true) {
                curLen = len[p];
                if (i - curLen - 1 >= 0 && s[i - curLen - 1] == s[i])
                    break;
                p = link[p];
            }
            if (next[p][ch]) {
                last = next[p][ch];
                pos[i] = last;
                continue;
            }
            last = tot++;
            pos[i] = last;
            len[last] = len[p] + 2;
            memset(next[last], 0, sizeof(next[last]));
            next[p][ch] = last;

            if (len[last] == 1) {
                link[last] = 1;
                continue;
            }

            while (true) {
                p = link[p];
                curLen = len[p];
                if (i - curLen - 1 >= 0 && s[i - curLen - 1] == s[i]) {
                    link[last] = next[p][ch];
                    break;
                }
            }
        }
    }

    void debug() {
        cout << "     i      link       ";
        for (int i = 0; i < 26; ++i)
            cout << setw(3) << (char) (i + 'a');
        cout << endl;
        for (int i = 0; i < tot; ++i) {
            cout << "i: " << setw(3) << i
                 << " link: " << setw(3) << link[i]
                 << " next: ";
            for (int j = 0; j < CHAR_NUM; ++j)
                cout << setw(3) << next[i][j];
            cout << endl;
        }
    }
} eer;
