/**
 * Title:   7-1UVa208
 * Author:  InvisibleMan
 * Data:    2017-1-6
 * Time:    0ms;
 */

// tips: 需要先判断是否存在可以到达k的路径，否则会超时

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
const int Nmax = 22;
int dst, way[Nmax], numW;
bool edge[Nmax][Nmax], vis[Nmax];

bool bfs() {
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int src = q.front(); q.pop();
        for(int i = 2; i < Nmax; i++) {
            if(edge[src][i] && !vis[i]) {
                if(i == dst) return true;
                vis[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}

void dfs(int now) {
    int src = way[now];
    if(src == dst) {
        printf("%d", way[0]);
        for(int i = 1; i <= now; i++)
            printf(" %d", way[i]);
        printf("\n");
        numW++;
        return;
    }
    for(int i = 2; i < Nmax; i++) {
        if(!edge[src][i] || vis[i]) continue;
        way[now + 1] = i;
        vis[i] = true;
        dfs(now + 1);
        vis[i] = false;
    }
}

int main() {
    int cnt = 0;
    while(scanf("%d", &dst) == 1) {
        numW = 0;
        memset(edge, 0, sizeof(edge));
        memset(vis, 0, sizeof(vis));
        vis[1] = true;
        way[0] = 1;
        int t1, t2;
        while(scanf("%d%d", &t1, &t2) == 2 && t1) {
            edge[t1][t2] = true;
            edge[t2][t1] = true;
        }
        printf("CASE %d:\n", ++cnt);
        if(bfs()) {
            memset(vis, 0, sizeof(vis));
            dfs(0);
        }
        printf("There are %d routes from the firestation to streetcorner %d.\n", numW, dst);
    }
}
