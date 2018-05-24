/**
 * Title:   POJ2342-3
 * Author:  InvisibleMan
 * Date:    2017-7-6
 * Time:    16ms
 */

// 参考网上的代码，把整棵树看成一个无根树
// 采用记忆化搜索的方法

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int Nmax = 6005;
struct Edge {
    int u, v, next;
};

Edge edge[Nmax << 1];
int n, tot, head[Nmax], value[Nmax], ans[Nmax][2]; 

void addEdge(int u, int v) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

int dfs(int now, int p, int exist) {
    if(ans[now][exist] > -1)
        return ans[now][exist];
    ans[now][exist] = 0;
    if(exist) {
        ans[now][exist] += max(value[now], 0);
        for(int i = head[now]; i > -1; i = edge[i].next)
            if(edge[i].v != p)
                ans[now][1] += max(dfs(edge[i].v, now, 0), 0);
    }
    else {
        for(int i = head[now]; i > -1; i = edge[i].next)
            if(edge[i].v != p)
                ans[now][0] += max(max(dfs(edge[i].v, now, 1), dfs(edge[i].v, now, 0)), 0);
    }
    return ans[now][exist];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &value[i]);
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(ans, -1, sizeof(ans));
    for(int i = 1; i < n; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        addEdge(t1 - 1, t2 - 1);
        addEdge(t2 - 1, t1 - 1);
    }
    printf("%d\n", max(dfs(0, -1, 0), dfs(0, -1, 1)));
    return 0;
}
