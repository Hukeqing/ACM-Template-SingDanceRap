void Manacher(char *s, int len, char *Ma, int *Mp)
{ // s 为被计算的串，len 为 s 的长度， Ma 和 Mp 需要两倍以上的 s 的长度
    int l = 0;
    Ma[l++] = '$';
    Ma[l++] = '#';
    for (int i = 0; i < len; i++)
    {
        Ma[l++] = s[i];
        Ma[l++] = '#';
    }
    Ma[l] = 0;
    int mx = 0, id = 0;
    for (int i = 0; i < l; i++)
    {
        Mp[i] = mx > i ? (Mp[2 * id - i] < mx - i ? Mp[2 * id - i] : mx - i) : 1;
        while (Ma[i + Mp[i]] == Ma[i - Mp[i]])
            Mp[i]++;
        if (i + Mp[i] > mx)
        {
            mx = i + Mp[i];
            id = i;
        }
    }
}
/*
 * abaaba
 * i:       0  1  2  3  4  5  6  7  8  9 10 11 12 13
 * Ma[i]:   $  #  a  #  b  #  a  #  a  #  b  #  a  #
 * Mp[i]:   1  1  2  1  4  1  2  7  2  1  4  1  2  1
 * Mp[i] - 1：为以该点为中心的回文串长度。
 */
