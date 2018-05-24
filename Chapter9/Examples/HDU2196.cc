/**
 * Title:   HDU2196
 * Author:  InvisibleMan
 * Date:    2017-7-6
 * Time:    46ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Nmax = 10005;

struct Edge {
    int u, v, d, next;
};

Edge edge[Nmax << 1];
int n, tot, head[Nmax], p[Nmax], ans[Nmax], deep[Nmax][2];

void addEdge(int u, int v, int d) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].d = d;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void findDeep(int now) {
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v && p[v] < 0) {
            p[v] = now;
            findDeep(v);
            int nowDeep = deep[v][0] + edge[i].d;
            if(nowDeep > deep[now][0]) {
                if(deep[now][0] > -1)
                    deep[now][1] = deep[now][0];
                deep[now][0] = nowDeep;
            }
            else if(nowDeep > deep[now][1]) deep[now][1] = nowDeep;
        }
    }
    if(deep[now][0] < 0)
        deep[now][0] = 0;
}

void findAns(int now, int pDeep) {
    ans[now] = max(deep[now][0], pDeep);
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(p[v] == now) {
            int newPDeep = pDeep + edge[i].d;
            if(deep[v][0] != deep[now][0] - edge[i].d)
                newPDeep = max(deep[now][0] + edge[i].d, newPDeep);
            else if(deep[now][1] > -1)
                newPDeep = max(deep[now][1] + edge[i].d, newPDeep);
            findAns(v, newPDeep);
        }
    }
}

int main() {
    while(scanf("%d", &n) == 1) {
        tot = 0;
        memset(head, -1, sizeof(head));
        memset(p, -1, sizeof(p));
        memset(deep, -1, sizeof(deep));
        for(int i = 1; i < n; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            addEdge(--t1, i, t2);
            addEdge(i, t1, t2);
        }
        findDeep(0);
        findAns(0, 0);
        for(int i = 0; i < n; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
