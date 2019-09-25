inline void read(__int128 &X) {
    X = 0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    if (w) X = -X;
}

inline void print(__int128 x) {
    if (!x) return;
    if (x < 0) putchar('-'), x = -x;
    print(x / 10);
    putchar(x % 10 + '0');
}