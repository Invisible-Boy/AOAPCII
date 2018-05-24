/**
 * Title:   9-13UVa1220
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
        d[nowP][1] += d[now][0];
    }
}

bool only(int now, int exist) {
    for(int i = head[now]; i > -1; i = edge[i].next) {
        int v = edge[i].v;
        if(p[v] == now) {
            if(!exist) {
                if(d[v][0] == d[v][1]) return false;
                else if(d[v][0] > d[v][1] && !only(v, 0)) return false;
                else if(d[v][1] > d[v][0] && !only(v, 1)) return false;
            }
            else if(!only(v, 0)) return false;
        }
    }
    return true;
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        int id = 0;
        tot = 0; idMp.clear();
        memset(head, -1, sizeof(head));
        memset(d, 0, sizeof(d));
        memset(p, -1, sizeof(p));
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
        bool flag = true;
        if(d[0][0] == d[0][1])
            flag = false;
        else if(d[0][0] > d[0][1])
            flag = only(0, 0);
        else
            flag = only(0, 1);
        printf("%s\n", flag ? "Yes" : "No");
    }
    return 0;
}
