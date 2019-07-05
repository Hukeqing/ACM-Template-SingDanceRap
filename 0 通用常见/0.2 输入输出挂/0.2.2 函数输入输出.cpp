/*
 * 用函数输入输出，可以判断EOF
 * 使用:
 * int a;
 * FastRead (a);
 */
template <class __T>
inline bool FastRead (__T& x) {
    x = 0; char f = 0; int ch = getchar(); double d = 0.1;
    if (ch == EOF) return false;
    while(ch > '9' || ch < '0') { f |= (ch == '-'); ch = getchar(); }
    while(ch <= '9' && ch >= '0') { x = x * 10 + ch - 48; ch = getchar(); }
    if (ch == '.') {
        ch = getchar();
        while(ch <= '9' && ch >= '0') { x += d * (ch - 48); d *= 0.1; ch = getchar(); }
    }
    return true;
}
template <class T>
inline void FastPrint(T &x)
{
    if (x > 9)FastPrint(x / 10);
    putchar(x % 10 + '0');
}