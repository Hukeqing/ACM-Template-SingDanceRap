/*
 * 扩展KMP算法
 */
// next[i]:x[i...m-1] 与 x[0...m-1] 的最长公共前缀长度
// extend[i]:y[i...n-1] 与 x[0...m-1] 的最长公共前缀长度
void pre_EKMP(char *x, int m, int *next) {
    next[0] = m;
    int j = 0;
    while (j + 1 < m && x[j] == x[j + 1]) j++;
    next[1] = j;
    int k = 1;
    for (int i = 2; i < m; i++) {
        int p = next[k] + k - 1;
        int L = next[i - k];
        if (i + L < p + 1) next[i] = L;
        else {
            j = 0 > p - i + 1 ? 0 : p - i + 1;
            while(i + j < m && x[i + j] == x[j]) j++;
            next[i] = j;
            k = i;
        }
    }
}
void EKMP(char *x, int m, char *y, int n, int *extend) {    //x、y 为字符串，一般把 x 作为较短的，m、n 分别为x、y的字符串长度，extend 为答案。
    int *next = new int[m + 5];
    pre_EKMP(x, m, next);
    int j = 0, k = 0;
    while (j < n && j < m && x[j] == y[j]) j++;
    extend[0] = j;
    for (int i = 1; i < n; i++) {
        int p = extend[k] + k - 1;
        int L = next[i - k];
        if (i + L < p + 1) extend[i] = L;
        else {
            j = 0 > p - i + 1 ? 0 : p - i + 1;
            while(i + j < n && j < m && y[i + j] == x[j] ) j++;
            extend[i] = j;
            k = i;
        }
    }
}
