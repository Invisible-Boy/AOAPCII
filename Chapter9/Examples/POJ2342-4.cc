/**
 * Title:   POJ2342-4
 * Author:  InvisibleMan
 * Date:    2017-7-6
 * Time:    0ms
 */

// 参考网上的代码，把整棵树看成一个无根树
// 采用刷表法

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int Nmax = 6005;
struct Edge {
    int u, v, next;
};

Edge edge[Nmax << 1];
int n, tot, head[Nmax], value[Nmax], ans[Nmax][2], p[Nmax]; 

void addEdge(int u, int v) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int now) {
    ans[now][0] = 0;
    ans[now][1] = max(value[now], 0);
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v && p[v] < 0) {
            p[v] = now;
            dfs(v);
        }
    }
    int nowP = p[now];
    if(nowP > -1) {
        ans[nowP][0] += max(ans[now][1], ans[now][0]);
        ans[nowP][1] += ans[now][0];
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &value[i]);
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(ans, -1, sizeof(ans));
    memset(p, -1, sizeof(p));
    for(int i = 1; i < n; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        addEdge(t1 - 1, t2 - 1);
        addEdge(t2 - 1, t1 - 1);
    }
    dfs(0);
    printf("%d\n", max(ans[0][0], ans[0][1]));
    return 0;
}
