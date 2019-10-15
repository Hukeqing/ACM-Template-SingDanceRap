
const double pi = acos(-1.0);
const int maxn = (int) 3e6 + 100;
int rev[maxn];
int m, n;

struct Complex {
    double x, y;

    Complex(double xx = 0, double yy = 0) {
        x = xx;
        y = yy;
    }
} com1[maxn], com2[maxn];

Complex operator+(Complex a, Complex b) {
    return Complex(a.x + b.x, a.y + b.y);
}

Complex operator-(Complex a, Complex b) {
    return Complex(a.x - b.x, a.y - b.y);
}

Complex operator*(Complex a, Complex b) {
    return Complex(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);
}

inline int quickread() {
    int k = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (isdigit(c)) k = (k << 1) + (k << 3) + c - 48, c = getchar();
    return k * f;
}

void FFT(int len, Complex *a, int flag) {
    for (int i = 0; i < len; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int j = 1; j < len; j <<= 1) {
        Complex wn(cos(pi / j), flag * sin(pi / j));
        for (int k = 0; k < len; k += (j << 1)) {
            Complex w0(1, 0);
            for (int i = 0; i < j; i++, w0 = w0 * wn) {
                Complex x = a[k + i], y = w0 * a[i + j + k];
                a[i + k] = x + y;
                a[i + k + j] = x - y;
            }
        }
    }
}

int main(void) {
    n = quickread(), m = quickread();
    for (int i = 0; i <= n; i++) {
        com1[i].x = quickread();
    }
    for (int j = 0; j <= m; j++) {
        com2[j].x = quickread();
    }
    int len = 1, l = 0;
    while (len <= n + m) len <<= 1, l++;
    for (int i = 0; i < len; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    }

    FFT(len, com1, 1);
    FFT(len, com2, 1);
    for (int i = 0; i <= len; i++) {
        com1[i] = com1[i] * com2[i];
    }
    FFT(len, com1, -1);
    for (int i = 0; i < n + m; i++) {
        printf("%d ", (int)(com1[i].x / len + 0.5));
    }
    printf("%d\n", int(com1[n + m].x / len + 0.5));
}