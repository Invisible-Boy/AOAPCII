/**
 * Title:   9-19UVa1627
 * Author:  InvisibleMan
 * Date:    2017-7-26
 * Time:    20ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 105;

int n, color[Nmax], colorMp[Nmax << 1][Nmax], NColor[Nmax << 1], tot, pre[Nmax][Nmax << 1];
bool adj[Nmax][Nmax], ans[Nmax][Nmax << 1], now[Nmax][Nmax << 1];

bool dfs(int now, int t1, int t2) {
    color[now] = t1;
    colorMp[t1][NColor[t1]++] = now;
    for(int i = 1; i <= n; i++)
        if(i != now && (!adj[now][i] || !adj[i][now]))
            if(color[i] == t1 || (color[i] == -1 && !dfs(i, t2, t1))) return false;
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(adj, false, sizeof(adj));
        memset(NColor, 0, sizeof(NColor));
        for(int i = 1; i <= n; i++) {
            int t;
            while(scanf("%d", &t) == 1 && t)
                adj[i][t] = true;
        }
        memset(color, -1, sizeof(color));
        tot = 0;
        bool flag = true;
        for(int i = 1; i <= n && flag; i++) {
            if(color[i] < 0) {
                flag = dfs(i, tot, tot + 1);
                tot += 2;
            }
        }
        if(flag) {
            memset(ans, 0, sizeof(ans));
            bool vis[Nmax] = {0};
            int diff = NColor[0] - NColor[1];
            ans[0][n + diff] = true; now[0][n + diff] = false; pre[0][n + diff] = -1;
            ans[0][n - diff] = true; now[0][n - diff] = true; pre[0][n - diff] = -1;
            for(int i = 1; i < (tot >> 1); i++) {
                diff = NColor[i << 1] - NColor[(i << 1) + 1];
                for(int j = 0; j <= n << 1; j++)
                    if(ans[i - 1][j]) {
                        ans[i][j + diff] = true; now[i][j + diff] = false; pre[i][j + diff] = j;
                        ans[i][j - diff] = true; now[i][j - diff] = true; pre[i][j - diff] = j;
                    }
            }
            diff = 0;
            while(diff <= n) {
                if(ans[(tot >> 1) - 1][diff + n])
                    break;
                diff++;
            }
            printf("%d", (n + diff) >> 1);
            int sta = n + diff;
            for(int i = (tot >> 1) - 1; i > -1; i--) {
                if(!now[i][sta]) {
                    int num = NColor[i << 1];
                    for(int j = 0; j < num; j++) {
                        int tt = colorMp[i << 1][j];
                        printf(" %d", tt);
                        vis[tt] = true;
                    }
                }
                else {
                    int num = NColor[(i << 1) + 1];
                    for(int j = 0; j < num; j++) {
                        int tt = colorMp[(i << 1) + 1][j];
                        printf(" %d", tt);
                        vis[tt] = true;
                    }
                }
                sta = pre[i][sta];
            }
            sta = (n - diff) >> 1;
            printf("\n%d", sta);
            for(int i = 1; i <= n; i++)
                if(!vis[i]) printf(" %d", i);
            printf("\n");
        }
        else
            printf("No solution\n");
        if(T) printf("\n");
    }
    return 0;
}
