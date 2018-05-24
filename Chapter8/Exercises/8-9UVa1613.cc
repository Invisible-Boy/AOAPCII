/**
 * Title:   8-9UVa1613
 * Author:  InvisibleMan
 * Date:    2017-4-29
 * Time:    80ms
 */

// 直接bfs，这题没有想到证明方法，感觉是玄学题

#include <cstdio>
#include <queue>
#include <vector>
#define max(x, y) ((x) > (y) ? (x) : (y))
using namespace std; 

int g[10000][10000];

int main() {
    int cnt = 0, n, m, edgeN[10000], c[10000];
    while(scanf("%d%d", &n, &m) == 2) {
        int t1, t2;
        for(int i = 0; i < n; i++)
            c[i] = -1, edgeN[i] = 0;
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &t1, &t2);
            --t1, --t2;
            g[t1][edgeN[t1]++] = t2;
            g[t2][edgeN[t2]++] = t1;
        }
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans = max(ans, edgeN[i]);
        ans |= 1;
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            int now = q.front(); q.pop();
            vector<bool> vis(ans + 1, false);
            for(int i = 0; i < edgeN[now]; i++) {
                int nei = g[now][i];
                if(c[nei] > 0) vis[c[nei]] = true;
                else if(c[nei] < 0) {
                    c[nei] = 0;
                    q.push(nei);
                }
            }
            for(int i = 1; i < ans + 1; i++)
                if(!vis[i]) {
                    c[now] = i;
                    break;
                }
        }
        if(cnt++) printf("\n");
        printf("%d\n", ans);
        for(int i = 0; i < n; i++)
            printf("%d\n", c[i]);

    }
    return 0;
}
