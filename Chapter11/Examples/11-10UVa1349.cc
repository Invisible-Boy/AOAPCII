/**
 *  Title:  11-10UVa1349
 *  Author: InvisibleMan
 *  Date:   2018/6/19
 */

#include <cstdio>
#include <queue>
#include <memory.h>

using namespace std;

const int Nmax = 205, Mmax = 80000;

struct Edge {
    int from, to, cost, next, c, f;
}edge[Mmax];

int tot, pHead[Nmax];

void addEdge(int from, int to, int cost, int c) {
    edge[tot].from = from;
    edge[tot].to = to;
    edge[tot].cost = cost;
    edge[tot].f = 0;
    edge[tot].c = c;
    edge[tot].next = pHead[from];
    pHead[from] = tot++;
}

int n;

bool init() {
    scanf("%d", &n);
    if(n == 0) return false;
    tot = 0;
    memset(pHead, -1, sizeof(pHead));
    for(int i = 1; i <= n; i++) {
        addEdge(0, i, 0, 1);
        addEdge(i, 0, 0, 0);
        addEdge(i + 100, n + 101, 0, 1);
        addEdge(n + 101, i + 100, 0, 0);
        int t1, t2;
        while((scanf("%d", &t1) == 1) && t1) {
            scanf("%d", &t2);
            addEdge(i, t1 + 100, t2, 1);
            addEdge(t1 + 100, i, -t2, 0);
        }
    }
    return true;
}

int EK() {
    int cnt = 0, ans = 0, p[Nmax], dist[Nmax];
    bool inq[Nmax];
    while(cnt < n) {
        memset(inq, false, sizeof(inq));
        memset(dist, 0x3f, sizeof(dist));
        memset(p, -1, sizeof(p));
        queue<int> q;
        q.push(0); inq[0] = true;
        dist[0] = 0;
        while(!q.empty()) {
            int now = q.front(); q.pop();
            inq[now] = false;
            for(int i = pHead[now]; i != -1; i = edge[i].next) {
                int to = edge[i].to;
                if(edge[i].f < edge[i].c && dist[now] + edge[i].cost < dist[to]) {
                    dist[to] = dist[now] + edge[i].cost;
                    p[to] = i;
                    if(!inq[to]) {
                        q.push(to);
                        inq[to] = true;
                    }
                }
            }
        }
        if(dist[n + 101] == 0x3f3f3f3f) break;
        cnt++;
        for(int i = p[n + 101]; i != -1; i = p[edge[i].from]) {
            edge[i].f += 1;
            edge[i ^ 1].f -= 1;
        }
        ans += dist[n + 101];
    }
    if(cnt != n) ans = -1;
    return ans;
}

int main() {
    while(init()) {
        int ans = EK();
        if(ans == -1) printf("N\n");
        printf("%d\n", ans);
    }
    return 0;
}
