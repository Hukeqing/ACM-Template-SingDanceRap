int binary_search(int l, int r, int value) {
    int mid, cnt = r - l;
    while (cnt > 0) {
        int step = cnt / 2;
        mid = l + step;
        if (mid < value) {
            l = mid + 1;
            cnt -= step + 1;
        } else
            cnt /= 2;
    }
    return l;
}
