struct HashData {
    int *hash_data;
    int r;

    // [1, n], 数组 a 将会被改变并作为 hash 数组
    void init(int *a, int n) {
        sort(a + 1, a + 1 + n);
        r = unique(a + 1, a + 1 + n) - a - 1;
        hash_data = a;
    }

    // 获得 x 的 hash 值
    int my_hash(int x) {
        return lower_bound(hash_data + 1, hash_data + 1 + r, x) - hash_data;
    }

    // 根据 hash 值返回原值
    int re_hash(int x) {
        return hash_data[x];
    }
};
