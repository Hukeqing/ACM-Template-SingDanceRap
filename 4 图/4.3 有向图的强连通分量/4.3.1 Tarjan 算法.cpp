/*
 *  Tarjan 算法
 * 复杂度 O(N + M)
 * 每组示例前先使用 init 函数
 * 然后用 addedge 添加边
 * 最后solve一下
 * 点编号 1 - n
 */

const int MAXN = 1100;  // 点数
const int MAXM = 1000100; // 边数
struct Edge {
    int to, next;
} edge[MAXM]; // 只有这里写的是 MAXM

int head[MAXN], tot;
int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN]; //Belong 数组的值是 1 ～ scc
int Index, top;
int scc; // 强连通分量的个数
bool Instack[MAXN];
int num[MAXN]; // 各个强连通分量包含点的个数，数组编号 1 ～ scc
// num 数组不一定需要，结合实际情况

void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void Tarjan(int u) {
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        v = edge[i].to;
        if (!DFN[v]) {
            Tarjan(v);
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
            Tarjan(i);
}

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}
