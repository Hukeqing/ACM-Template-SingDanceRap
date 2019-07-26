/*
 * 模拟流输入输出，无法判断EOF
 * 使用:
 * int a;
 * io>>a;
 */
struct ioss
{
#define endl '\n'
    static const int LEN = 20000000;
    char obuf[LEN], *oh = obuf;
    std::streambuf *fb;
    ioss()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        fb = cout.rdbuf();
    }
    inline char gc()
    {

        static char buf[LEN], *s, *t, buf2[LEN];
        return (s == t) && (t = (s = buf) + fread(buf, 1, LEN, stdin)), s == t ? -1 : *s++;
    }
    inline ioss &operator>>(long long &x)
    {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
            sgn |= ch == '-';
        }
        for (x = 0; isdigit(ch); ch = gc())
            x = x * 10 + (ch ^ '0');
        sgn && (x = -x);
        return *this;
    }
    inline ioss &operator>>(int &x)
    {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
            sgn |= ch == '-';
        }
        for (x = 0; isdigit(ch); ch = gc())
            x = x * 10 + (ch ^ '0');
        sgn && (x = -x);
        return *this;
    }
    inline ioss &operator>>(char &x)
    {
        static char ch;
        for (; !isalpha(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
        }
        x = ch;
        return *this;
    }
    inline ioss &operator>>(string &x)
    {
        static char ch, *p, buf2[LEN];
        for (; !isalpha(ch) && !isdigit(ch); ch = gc())
            if (ch == -1)
                return *this;
        p = buf2;
        for (; isalpha(ch) || isdigit(ch); ch = gc())
            *p = ch, p++;
        *p = '\0';
        x = buf2;
        return *this;
    }
    inline ioss &operator<<(string &c)
    {
        for (auto &p : c)
            this->operator<<(p);
        return *this;
    }
    inline ioss &operator<<(const char *c)
    {
        while (*c != '\0')
        {
            this->operator<<(*c);
            c++;
        }
        return *this;
    }
    inline ioss &operator<<(const char &c)
    {
        oh == obuf + LEN ? (fb->sputn(obuf, LEN), oh = obuf) : 0;
        *oh++ = c;
        return *this;
    }
    inline ioss &operator<<(int x)
    {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'), x = -x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10)
            buf[++cnt] = x % 10 | 48;
        while (cnt)
            this->operator<<((char)buf[cnt--]);
        return *this;
    }
    inline ioss &operator<<(long long x)
    {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'), x = -x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10)
            buf[++cnt] = x % 10 | 48;
        while (cnt)
            this->operator<<((char)buf[cnt--]);
        return *this;
    }
    ~ioss()
    {
        fb->sputn(obuf, oh - obuf);
    }
} io;