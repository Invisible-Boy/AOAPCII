/**
 *  Title:  11-11UVa12661
 *  Author: InvisibleMan
 *  Date:   2018/6/20
 *  Time:   50ms
 */

#include <cstdio>
#include <queue>
#include <memory.h>

using namespace std;

const int Nmax = 305, Mmax = 50005;

struct Edge {
    int to, a, b, t, next;
}edge[Mmax];

int tot, pHead[Nmax];

void addEdge(int from, int to, int a, int b, int cost) {
    edge[tot].to = to;
    edge[tot].a = a;
    edge[tot].b = b;
    edge[tot].t = cost;
    edge[tot].next = pHead[from];
    pHead[from] = tot++;
}

int n, m, src, dst;

struct Node {
    Node(int _id, int _cost) : id(_id), cost(_cost) {}
    int id, cost;
    bool operator < (const Node &rhs) const {
         return cost > rhs.cost;
    }
};

int dijkstra() {
    int ans = 0, dist[Nmax];
    bool vis[Nmax] = {0};
    memset(dist, 0x1f, sizeof(dist));
    priority_queue<Node> q;
    q.push(Node(src, 0));
    dist[src] = 0;
    while(!q.empty()) {
        int now = q.top().id, cost = q.top().cost; q.pop();
        if(now == dst) {
            ans = cost;
            break;
        }
        if(vis[now]) continue;
        vis[now] = true;
        for(int i = pHead[now]; i != -1; i = edge[i].next) {
            int to = edge[i].to, t1 = edge[i].a, t2 = edge[i].b, t = t1 + t2, nowt = cost;
            if(nowt % t > t1) nowt = (nowt / t) * t + t;
            nowt += edge[i].t;
            if(nowt % t > t1) nowt = (nowt / t) * t + t + edge[i].t;
            if(nowt < dist[to]) {
                dist[to] = nowt;
                q.push(Node(to, nowt));
            }
        }
    }
    return ans;
}

int main() {
    int kase = 1;
    while(scanf("%d%d%d%d", &n, &m, &src, &dst) == 4) {
        memset(pHead, -1, sizeof(pHead));
        tot = 0;
        for(int i = 0; i < m; i++) {
            int u, v, a, b, t;
            scanf("%d%d%d%d%d", &u, &v, &a, &b, &t);
            if(t <= a) addEdge(u, v, a, b, t);
        }
        printf("Case %d: %d\n", kase++, dijkstra());
    }
    return 0;
}
