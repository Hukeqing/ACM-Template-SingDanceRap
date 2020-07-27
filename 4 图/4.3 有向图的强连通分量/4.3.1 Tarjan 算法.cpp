struct Tarjan {
    int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN]; //Belong 数组的值是 1 ～ scc
    int Index, top;
    int scc; // 强连通分量的个数
    bool Instack[MAXN];
    int num[MAXN]; // 各个强连通分量包含点的个数，数组编号 1 ～ scc

    void _tarjan(int u) {
        int v;
        Low[u] = DFN[u] = ++Index;
        Stack[top++] = u;
        Instack[u] = true;
        for (int i = graph.head[u]; i != -1; i = graph.edge[i].next) {
            v = graph.edge[i].to;
            if (!DFN[v]) {
                _tarjan(v);
                if (Low[u] > Low[v])
                    Low[u] = Low[v];
            } else if (Instack[v] && Low[u] > DFN[v])
                Low[u] = DFN[v];
        }
        if (Low[u] == DFN[u]) {
            scc++;
            do {
                v = Stack[--top];
                Instack[v] = false;
                Belong[v] = scc;
                num[scc]++;
            } while (v != u);
        }
    }

    void solve(int N) {
        memset(DFN, 0, sizeof(DFN));
        memset(Instack, false, sizeof(Instack));
        memset(num, 0, sizeof(num));
        Index = scc = top = 0;
        for (int i = 1; i <= N; i++)
            if (!DFN[i])
                _tarjan(i);
    }
} tarjan;
