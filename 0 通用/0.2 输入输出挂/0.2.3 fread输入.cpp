/*
 * fread快读，最强快读
 * 不可以与其他任何读入重用
 * 可以判断是否为文件结束
 * 使用:
 * int a;
 * FastRead (a);
 */
struct fastio
{
    static const int s = 1 << 24;
    unsigned p, l;
    fastio() { p = l = 0; }
    char gc()
    {
        static char bf[s];
        if (p == l)
            p = 0, l = fread(bf, 1, s, stdin);
        return p == l ? -1 : bf[p++];
    }
    template <class __T>
    bool read(__T &x)
    {
        char c = gc(), f = 0;
        double d = 0.1;
        while ((c < '0' || c > '9') && ~c) {f |= (c == '-'); c = gc(); }
        if (c == -1) return 0;
        x = 0;
        while (c <= '9' && c >= '0') { x = x * 10 + c - '0'; c = gc(); }
        if (c == '.') {
            c = gc(); 
            while(c <= '9' && c >= '0') { x += d * (c - '0'); d *= 0.1; ch = gc(); }
        }
        return 1;
    }
} io;