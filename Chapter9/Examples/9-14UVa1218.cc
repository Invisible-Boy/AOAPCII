/**
 * Title:   9-14UVa1218
 * Author:  InvisibleMan
 * Date:    2017-7-15
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, next;
};

const int Nmax = 1e4;
/**
 *ans[i][0] : i节点父亲不是服务器，i节点不是服务器
 *ans[i][1] : i节点父亲不是服务器，i节点是服务器
 *ans[i][2] : i节点父亲是服务器，i节点不是服务器
 *ans[i][3] : i节点父亲是服务器，i节点是服务器
 *其中ans[i][1]和ans[i][3]可以合并
 */
int tot, head[Nmax], ans[Nmax][4], p[Nmax];
Edge edge[Nmax << 1];

void addEdge(int u, int v) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int now) {
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v && p[v] == -1) {
            p[v] = now;
            dfs(v);
            ans[now][1] += min(ans[v][2], ans[v][3]);
            ans[now][2] += ans[v][0];
            ans[now][3] += min(ans[v][2], ans[v][3]);
        }
    }
    int &add = ans[now][0], sum = ans[now][2];
    add = Nmax;
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(p[v] == now)
            add = min(add, sum - ans[v][0] + ans[v][1]);
    }
}

int main() {
    int n;
    while((scanf("%d", &n) == 1) && n > -1) {
        tot = 0;
        for(int i = 0; i < n; i++) {
            head[i] = -1;
            ans[i][0] = 0; ans[i][2] = 0;
            ans[i][1] = 1; ans[i][3] = 1;
            p[i] = -1;
        }
        int t1, t2;
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &t1, &t2);
            addEdge(--t1, --t2);
            addEdge(t2, t1);
        }
        if(n == 0) printf("0\n");
        else if(n < 4) printf("1\n");
        else {
            dfs(0);
            printf("%d\n", min(ans[0][0], ans[0][1]));
        }
        scanf("%d", &t1);
        if(t1 < 0) break;
    }
    return 0;
}
