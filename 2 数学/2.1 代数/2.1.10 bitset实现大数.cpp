// 加法
void add(const bitset<MAXN> &a, const bitset<MAXN> &b, bitset<MAXN> &c)
{
    bitset<MAXN> c = a ^ b;
    bitset<MAXN> ap = c;
    bitset<MAXN> bp = (b & a) << 1;
    while (bp.any())
    {
        c = ap ^ bp;
        bp = (ap & bp) << 1;
    }
}
// 取负值
void neg(const bitset<MAXN> &a, bitset<MAXN> &c)
{
    c = a.flip();
    int idx = 0;
    while (idx < c.size() && c.test(idx))
    {
        c[idx] = 0;
        idx++;
    }
    c[idx] = 1;
}