/**
 *  Title:  11-9UVa1658-2
 *  Author: InvisibleMan
 *  Date:   2018/6/19
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int Nmax = 1005, Mmax = 11005;

int n, m;

struct Edge {
    int from, to, cost, f, c, next;
}edge[Mmax << 1];

int tot, pHead[Nmax << 1];

void addEdge(int from, int to, int cost, int c) {
    edge[tot].from = from;
    edge[tot].to = to;
    edge[tot].cost = cost;
    edge[tot].f = 0;
    edge[tot].c = c;
    edge[tot].next = pHead[from];
    pHead[from] = tot++;
}

void init() {
    memset(pHead, -1, sizeof(pHead));
    tot = 0;
    for(int i = 2; i < n; i++) {
        addEdge(i, i + Nmax, 0, 1);
        addEdge(i + Nmax, i, 0, 0);
    }
    for(int i = 0; i < m; i++) {
        int t1, t2, cost;
        scanf("%d%d%d", &t1, &t2, &cost);
        if(t1 != 1 && t1 != n) t1 += Nmax;
        addEdge(t1, t2, cost, 1);
        addEdge(t2, t1, -cost, 0);
    }
    addEdge(0, 1, 0, 2);
    addEdge(1, 0, 0, 0);
}

int EK() {
    int dist[Nmax << 1], p[Nmax << 1];
    bool inq[Nmax << 1];
    int ans = 0;
    while(1) {
        memset(dist, 0x1f, sizeof(dist));
        memset(p, -1, sizeof(p));
        memset(inq, 0, sizeof(inq));
        dist[0] = 0; inq[0] = true;
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            inq[now] = false;
            for(int i = pHead[now]; i != -1; i = edge[i].next) {
                int to = edge[i].to;
                if(edge[i].f < edge[i].c && dist[now] + edge[i].cost < dist[to]) {
                    dist[to] = dist[now] + edge[i].cost;
                    p[to] = i;
                    if(!inq[to]) {
                        inq[to] = true;
                        q.push(to);
                    }
                }
            }
        }
        if(dist[n] == 0x1f1f1f1f) break;
        ans += dist[n];
        for(int i = p[n]; i != -1; i = p[edge[i].from]) {
            edge[i].f += 1;
            edge[i ^ 1].f -= 1;
        }
    }
    return ans;
}

int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        init();
        printf("%d\n", EK());
    }
    return 0;
}
