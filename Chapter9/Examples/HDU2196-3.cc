/**
 * Title:   HDU2196-3
 * Author:  InvisibleMan
 * Date:    2017-7-6
 * Time:    46ms
 */

/**
 * 经过思考发现，可以先找到一条直径，则每个节点的最远点一定在直径的两端
 *  *---*---*---*---*---*---*---*---*
 *          |   |       |
 *          *   *       *
 *          |
 *          *
 * 则一棵树可以抽象为上图所示，很容易理解为什么是直径的两端
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int Nmax = 10005;
struct Edge {
    int u, v, d, next;
};
int n, tot, head[Nmax], dist[Nmax], dist1[Nmax];
Edge edge[Nmax << 1];

void addEdge(int u, int v, int d) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    edge[tot].d = d;
    head[u] = tot++;
}

queue<int> q;
int bfs(int x) {
    q.push(x);
    memset(dist, -1, sizeof(dist));
    dist[x] = 0;
    int maxId = 0;
    while(!q.empty()) {
        x = q.front(); q.pop();
        if(dist[x] > dist[maxId])
            maxId = x;
        for(int i = head[x]; i > -1; i = edge[i].next) {
            int v = edge[i].v;
            if(dist[v] < 0) {
                dist[v] = dist[x] + edge[i].d;
                q.push(v);
            }
        }
    }
    return maxId;
}
int main() {
    while(scanf("%d", &n) != EOF) {
        tot = 0;
        memset(head, -1, sizeof(head));
        for(int i = 1; i < n; i++) {
            int v, d;
            scanf("%d%d", &v, &d);
            addEdge(i, --v, d);
            addEdge(v, i, d);
        }
        int edgeId = bfs(0);
        edgeId = bfs(edgeId);
        memcpy(dist1, dist, sizeof(dist));
        bfs(edgeId);
        for(int i = 0; i < n; i++)
            printf("%d\n", max(dist[i], dist1[i]));
    }
    return 0;
}
