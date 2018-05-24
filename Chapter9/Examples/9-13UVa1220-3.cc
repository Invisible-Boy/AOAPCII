/**
 * Title:   9-13UVa1220-3
 * Author:  InvisibleMan
 * Date:    2017-7-7
 * Time:    0ms
 */

#include <cstdio>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int Nmax = 205;

struct Edge{
    int u, v, next;
};

int n, tot, head[Nmax], d[Nmax][2], p[Nmax];
Edge edge[Nmax];
map<string, int> idMp;
bool flag[Nmax][2];

void addEdge(int u, int v) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int now) {
    d[now][1] = 1;
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v && p[v] < 0) {
            p[v] = now;
            dfs(v);
        }
    }
    int nowP = p[now];
    if(nowP > -1) {
        d[nowP][0] += max(d[now][1], d[now][0]);
        if(d[now][0] == d[now][1] || 
          (d[now][0] > d[now][1] && !flag[now][0]) ||
          (d[now][0] < d[now][1] && !flag[now][1])) flag[nowP][0] = false;
        d[nowP][1] += d[now][0];
        if(!flag[now][0]) flag[nowP][1] = false;
    }
}


int main() {
    while(scanf("%d", &n) == 1 && n) {
        int id = 0;
        tot = 0; idMp.clear();
        memset(head, -1, sizeof(head));
        memset(d, 0, sizeof(d));
        memset(p, -1, sizeof(p));
        memset(flag, -1, sizeof(flag));
        string temp(Nmax, 'a');
        scanf("%s", &temp[0]);
        idMp[temp] = id++;
        for(int i = 1; i < n; i++) {
            string temp1(Nmax, 'a'), temp2(Nmax, 'a');
            scanf("%s", &temp1[0]);
            scanf("%s", &temp2[0]);
            if(!idMp.count(temp1))
                idMp[temp1] = id++;
            if(!idMp.count(temp2))
                idMp[temp2] = id++;
            int t1 = idMp[temp1], t2 = idMp[temp2];
            addEdge(t2, t1);
        }
        dfs(0);
        printf("%d ", max(d[0][0], d[0][1]));
        bool f = true;
        if(d[0][0] == d[0][1]) f = false;
        else if(d[0][0] > d[0][1]) f = flag[0][0];
        else f = flag[0][1];
        printf("%s\n", f ? "Yes" : "No");
    }
    return 0;
}
