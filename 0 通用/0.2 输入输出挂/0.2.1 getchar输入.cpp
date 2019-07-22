/*
 * 模拟流输入输出，无法判断EOF
 * 使用:
 * int a;
 * rin>>a;
 */
struct FastIO {
    inline FastIO& operator >> (int& x) {
        x = 0; char f = 0, ch = getchar();
        while(ch > '9' || ch < '0') {f |= (ch == '-'); ch = getchar();}
        while(ch <= '9' && ch >= '0') {x = x * 10 + ch - 48; ch = getchar();}
        x = (f ? -x : x);
        return *this;
    }
    inline FastIO& operator >> (long long& x) {
        x = 0; char f = 0, ch = getchar();
        while(ch > '9' || ch < '0') {f |= (ch == '-'); ch = getchar();}
        while(ch <= '9' && ch >= '0') {x = x * 10 + ch - 48; ch = getchar();}
        x = (f ? -x : x);
        return *this;
    }
    inline FastIO& operator >> (double& x) {
        x = 0; char f = 0, ch = getchar();
        double d = 0.1;
        while(ch > '9' || ch < '0') {f |= (ch == '-'); ch = getchar();}
        while(ch <= '9' && ch >= '0') {x = x * 10 + ch - 48; ch = getchar();}
        if(ch == '.') {
            ch = getchar();
            while(ch <= '9' && ch >= '0') {x += d * (ch - 48); d *= 0.1; ch = getchar();}
        }
        x = (f ? -x : x);
        return *this;
    }
}rin;